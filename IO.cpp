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
        mapData.map = std::make_unique<std::vector<std::vector<Tile>>>();

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

            mapData.map->push_back(newRow); // Add the new row to the map
            row_number++;
        }

        if (mapData.map->size() != (mapData.radius) * 2 + 1)
        {
            throw std::runtime_error("Error: Map size does not match the radius specified.");
            return std::nullopt;
        }

        inFile.close();
        return mapData;
    } // loadmap
/////////////////////////////////////// - loadMap - /////////////////////////////////////////////
#pragma endregion
#pragma region savemap
/////////////////////////////////////// - saveMap - /////////////////////////////////////////////
    bool saveMap(const MapData& mapData, const std::string& fileName)
    {
        std::ofstream outFile(fileName);
        if (!outFile.is_open())
        {
            std::cerr << "Error: Could not open file " << fileName << std::endl;
            return false;
        }

        // Save radius, tile shape and orientation
        outFile << "radius:" << mapData.radius << std::endl;
        outFile << "tileShape:" << mapData.tileShape << std::endl;

        // Save map
        for (const auto& row : *mapData.map)
        {
            bool first = true;
            for (const auto& tile : row)
            {
                if (!first)
                {
                    outFile << ",";
                }
                if (tile.landscape == Landscape::Mountain)
                {
                    outFile << " " << MountainCharacter << " ";
                }
                else if (tile.landscape == Landscape::Grassland)
                {
                    outFile << " " << GrasslandCharacter << " ";
                }
                else
                {
                    outFile << ' ';
                }
                first = false;
            }
            outFile << std::endl;  // end of row
        }

        outFile.close();
        return true;
    } // savemap
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
        default:
            throw std::runtime_error("Error, Invalid tileShape!");
        }

    } // printMap
    void printSquareMap(const MapData& mapData, const std::vector<Coordinates>& path)
    {
        std::cout << "\n__" << std::string(mapData.map->size() * 4, '_');

        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // Get console handle

        for (const auto& row : *mapData.map)
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

        std::cout << "\n__" << std::string(mapData.map->size() * 4, '_');
    } // printSquareMap
/////////////////////////////////// - printMap functions - //////////////////////////////////////
#pragma endregion
} // namespace TileMap