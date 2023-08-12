#include "IO.h"

namespace TileMap
{
#pragma region loadmap
    /////////////////////////////////////// - loadMap - /////////////////////////////////////////////
    std::unique_ptr<MapData> loadMap(const std::string& fileName)
    {
        std::cout << "\ninput: " << fileName << "\n";
        std::ifstream inFile(fileName + FileExtension);
        std::string line;
        if (!inFile.is_open())
        {
            throw std::runtime_error("Error: Could not open file " + fileName);
            return nullptr;
        }

        // Load radius, tileShape
        if (!std::getline(inFile, line)) return nullptr;
        TileShape tileShape{ stringToTileShape(line.substr(line.find(':') + 1)) };
        if (!std::getline(inFile, line)) return nullptr;
        int16_t radius{ static_cast<int16_t>(stoi(line.substr(line.find(':') + 1))) };

        // Generate mapData of the appropriate type
        std::unique_ptr<MapData> mapData = generateMapData(tileShape, radius);
        Map newMap{};

        auto loadSquareMap = [&](Map& newMap) {
                int16_t row_number = -radius;
                while (std::getline(inFile, line))
                {
                    // removing whitespace from the line
                    line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());
                    // error handling: check if line length equals expected map width
                    if (line.length() != (radius) * 2 + 1)
                    {
                        throw std::runtime_error("Error: Map size does not match the radius specified.");
                        return nullptr;
                    }

                    std::vector<Tile> newRow; // Create a new row

                    int16_t column_number = -radius; // start from -radius
                    for (char c : line)
                    {
                        Coordinates coordinates = { column_number, row_number };
                        if (c == MountainCharacter)
                        {
                            newRow.push_back(Tile{ coordinates, Landscape::Mountain });
                        }
                        else if (c == GrasslandCharacter)
                        {
                            newRow.push_back(Tile{ coordinates, Landscape::Grassland });
                        }

                        column_number++;
                    }

                    newMap.push_back(newRow); // Add the new row to the map
                    row_number++;
                }

                if (newMap.size() != radius * 2 + 1)
                {
                    throw std::runtime_error("Error: Map size does not match the radius specified.");
                    return nullptr;
                }
            }; // ^ loadSquareMap ^
        auto loadHexMap = [&](Map& newMap) {
                int16_t row_number = 0;
                while (std::getline(inFile, line))
                {
                    // removing whitespace from the line
                    line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());

                    std::vector<Tile> newRow; // Create a new row

                    // start column_number based on row_number to ensure the center is (0,0)
                    int16_t column_number = 0 - row_number;
                    if (row_number > radius) column_number += (row_number - radius);
                    for (char c : line)
                    {
                        Coordinates coordinates = { column_number, row_number - radius };

                        if (c == MountainCharacter)
                        {
                            newRow.push_back(Tile{ coordinates, Landscape::Mountain });
                        }
                        else if (c == GrasslandCharacter)
                        {
                            newRow.push_back(Tile{ coordinates, Landscape::Grassland });
                        }

                        column_number++;
                    }

                    newMap.push_back(newRow); // Add the new row to the map
                    row_number++;
                }
            }; // ^ loadHexMap ^
        
        switch (tileShape)
        {
        case TileShape::Square:
            loadSquareMap(newMap);
            break;
        case TileShape::Hex:
            loadHexMap(newMap);
            break;
        default:
            throw std::runtime_error("Error, Invalid tileShape!");
        };

        if (newMap.size() != radius * 2 + 1)
        {
            throw std::runtime_error("Error: Map size does not match the radius specified.");
            return nullptr;
        }
        
        mapData->setMap(newMap);

        inFile.close();
        return mapData;
    } // loadmap
/////////////////////////////////////// - loadMap - /////////////////////////////////////////////
#pragma endregion
#pragma region printMap
/////////////////////////////////// - printMap functions - //////////////////////////////////////
    void printMap(const MapData& mapData, const std::vector<Coordinates>& path)
    {
        switch (mapData.getTileShape())
        {
        case (TileShape::Square):
            printSquareMap(mapData, path);
            break;
        case (TileShape::Hex):
            printHexMap(mapData, path);
            break;
        default:
            throw std::runtime_error("Error, Invalid tileShape!");
        }

    } // printMap
    void printSquareMap(const MapData& mapData, const std::vector<Coordinates>& path)
    {
        Map map = mapData.getMap();

        std::cout << "\n__" << std::string(map.size() * 4, '_');

        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // Get console handle

        for (const auto& row : map)
        {
            std::cout << "\n";
            for (const auto& tile : row)
            {
                // Check if tile is in path
                if (std::find(path.begin(), path.end(), tile.coordinates) != path.end())
                {
                    SetConsoleTextAttribute(hConsole, 2); // Set text color to green
                    std::cout << " @ ";                   // Print @ if tile is in path
                    SetConsoleTextAttribute(hConsole, 7); // Set text color back to white
                }
                else // If tile is not in path, print according to its landscape
                {
                    switch (tile.landscape)
                    {
                    case Landscape::Grassland:
                        std::cout << " . ";
                        break;
                    case Landscape::Mountain:
                        std::cout << " X ";
                        break;
                    default:
                        std::cout << " ? ";
                        break;
                    }
                }
            }
        }

        std::cout << "\n__" << std::string(map.size() * 4, '_');
    } // printSquareMap
    void printHexMap(const MapData& mapData, const std::vector<Coordinates>& path)
    {
        Map map = mapData.getMap();

        std::cout << "\n__" << std::string(map.size() * 4, '_');

        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // Get console handle

        bool oddRow = true;
        int y = 0;
        for (const auto& row : map)
        {
            //std::cout << "\n" << abs(mapData.radius + 1 - y);
            std::wcout << std::endl;

            // Indent each row proportional to its distance from the center
            std::cout << std::string(abs(mapData.getRadius() - y) * 1, ' ');

            for (const auto& tile : row)
            {
                // Check if tile is in path
                if (std::find(path.begin(), path.end(), tile.coordinates) != path.end())
                {
                    SetConsoleTextAttribute(hConsole, 2); // Set text color to green
                    std::cout << " @";                   // Print @ if tile is in path
                    SetConsoleTextAttribute(hConsole, 7); // Set text color back to white
                }
                else // If tile is not in path, print according to its landscape
                {
                    switch (tile.landscape)
                    {
                    case Landscape::Grassland:
                        std::cout << " .";
                        break;
                    case Landscape::Mountain:
                        std::cout << " X";
                        break;
                    default:
                        std::cout << " ?";
                        break;
                    }
                }
            }
            y++;
            oddRow = !oddRow; // Flip oddRow flag for next row
        } // for ( row : map )

        std::cout << "\n__" << std::string(map.size() * 4, '_');
    } // printHexMap

/////////////////////////////////// - printMap functions - //////////////////////////////////////
#pragma endregion
} // namespace TileMap