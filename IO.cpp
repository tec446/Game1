#include "IO.h"

namespace TileMap
{
#pragma region loadmap
    /////////////////////////////////////// - loadMap - /////////////////////////////////////////////
    std::optional<MapData> loadMap(const std::string& fileName)
    {
        std::cout << "\ninput: " << fileName << "\n";
        std::ifstream inFile(fileName + FileExtension);
        std::string line;
        if (!inFile.is_open())
        {
            throw std::runtime_error("Error: Could not open file " + fileName);
            return std::nullopt;
        }

        MapData mapData;

        // Load radius, tileShape and tileOrientation
        if (!std::getline(inFile, line)) return std::nullopt;
        mapData.radius = stoi(line.substr(line.find(':') + 1));
        if (!std::getline(inFile, line)) return std::nullopt;
        mapData.tileShape = stringToTileShape(line.substr(line.find(':') + 1));

        int16_t row_number = -mapData.radius;
        while (std::getline(inFile, line))
        {
            // removing whitespace from the line
            line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());
            // error handling: check if line length equals expected map width
            if (line.length() != (mapData.radius) * 2 + 1)
            {
                throw std::runtime_error("Error: Map size does not match the radius specified.");
                return std::nullopt;
            }

            std::vector<Tile> newRow; // Create a new row

            int16_t column_number = -mapData.radius; // start from -radius
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

            mapData.map.push_back(newRow); // Add the new row to the map
            row_number++;
        }

        if (mapData.map.size() != (mapData.radius) * 2 + 1)
        {
            throw std::runtime_error("Error: Map size does not match the radius specified.");
            return std::nullopt;
        }

        inFile.close();
        return mapData;
    } // loadmap
    std::optional<MapData> loadHexagonMap(const std::string& fileName)
    {
        std::cout << "\ninput: " << fileName << "\n";
        std::ifstream inFile(fileName + FileExtension);
        std::string line;
        if (!inFile.is_open())
        {
            throw std::runtime_error("Error: Could not open file " + fileName);
            return std::nullopt;
        }

        MapData mapData;

        // Load radius, tileShape
        if (!std::getline(inFile, line)) return std::nullopt;
        mapData.radius = stoi(line.substr(line.find(':') + 1));
        if (!std::getline(inFile, line)) return std::nullopt;
        mapData.tileShape = stringToTileShape(line.substr(line.find(':') + 1));

        int16_t row_number = 0;
        while (std::getline(inFile, line))
        {
            // removing whitespace from the line
            line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());

            std::vector<Tile> newRow; // Create a new row

            // start column_number based on row_number to ensure the center is (0,0)
            //int16_t column_number = (row_number > 0) ? row_number : 0;
            int16_t column_number = 0 - row_number;
            if (row_number > mapData.radius) column_number += (row_number - mapData.radius);
            for (char c : line)
            {
                Coordinates coordinates  = { column_number, row_number - mapData.radius};
                
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

            mapData.map.push_back(newRow); // Add the new row to the map
            row_number++;
        }

        inFile.close();
        return mapData;
    } // loadHexagonMap
/////////////////////////////////////// - loadMap - /////////////////////////////////////////////
#pragma endregion
#pragma region savemap
/////////////////////////////////////// - saveMap - /////////////////////////////////////////////
/////////////////////////////////////// - saveMap - /////////////////////////////////////////////
#pragma endregion
#pragma region printMap
/////////////////////////////////// - printMap functions - //////////////////////////////////////
    void printMap(const MapData& mapData, const std::vector<Coordinates>& path)
    {
        switch (mapData.tileShape)
        {
        case (TileShape::Square):
            printSquareMap(mapData, path);
            break;
        case (TileShape::Hexagon):
            printHexagonMap(mapData, path);
            break;
        default:
            throw std::runtime_error("Error, Invalid tileShape!");
        }

    } // printMap
    void printSquareMap(const MapData& mapData, const std::vector<Coordinates>& path)
    {
        std::cout << "\n__" << std::string(mapData.map.size() * 4, '_');

        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // Get console handle

        for (const auto& row : mapData.map)
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

        std::cout << "\n__" << std::string(mapData.map.size() * 4, '_');
    } // printSquareMap
    void printHexagonMap(const MapData& mapData, const std::vector<Coordinates>& path)
    {
        std::cout << "\n__" << std::string(mapData.map.size() * 4, '_');

        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // Get console handle

        bool oddRow = true;
        int y = 0;
        for (const auto& row : mapData.map)
        {
            //std::cout << "\n" << abs(mapData.radius + 1 - y);
            std::wcout << std::endl;

            // Indent each row proportional to its distance from the center
            std::cout << std::string(abs(mapData.radius - y) * 1, ' ');

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

        std::cout << "\n__" << std::string(mapData.map.size() * 4, '_');
    } // printHexagonMap

/////////////////////////////////// - printMap functions - //////////////////////////////////////
#pragma endregion
} // namespace TileMap