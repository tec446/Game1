#include "TileMapIO.h"

namespace TileMapIO
{
    std::optional<TMO::MapData> loadTileMap(const std::string& inputFilePath)
    {
        std::cout << "\ninput: " << inputFilePath << "\n";
        std::ifstream inFile(inputFilePath + FileExtension);
        std::string line;
        if (!inFile.is_open())
        {
            throw std::runtime_error("Error: Could not open file " + inputFilePath);
            return std::nullopt;
        }

        TMO::MapData mapData;

        // Load radius, tileShape and tileOrientation
        if (!std::getline(inFile, line)) return std::nullopt;
        mapData.radius = stoi(line.substr(line.find(':') + 1));
        if (!std::getline(inFile, line)) return std::nullopt;
        mapData.tileShape = TMO::stringToTileShape(line.substr(line.find(':') + 1));
        if (!std::getline(inFile, line)) return std::nullopt;
        mapData.tileOrientation = TMO::stringToTileOrientation(line.substr(line.find(':') + 1));

        int row_number = -mapData.radius;
        while (std::getline(inFile, line))
        {
            // removing whitespace from the line
            line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());
            // error handling: check if line length equals expected map width
            if (line.length() != mapData.radius * 2 + 1)
            {
                throw std::runtime_error("Error: Map size does not match the radius specified.");
                return std::nullopt;
            }

            std::vector<TMO::Tile> newRow; // Create a new row

            int column_number = -mapData.radius; // start from -radius
            for (char c : line)
            {
                TMO::Coordinates coordinates = { row_number, column_number };
                if (c == MountainCharacter)
                {
                    newRow.push_back(TMO::Tile{ coordinates, TMO::Landscape::Mountain });
                }
                else if (c == GrasslandCharacter)
                {
                    newRow.push_back(TMO::Tile{ coordinates, TMO::Landscape::Grassland });
                }

                column_number++;
            }

            mapData.map.push_back(newRow); // Add the new row to the map
            row_number++;
        }

        if (mapData.map.size() != mapData.radius * 2 + 1)
        {
            throw std::runtime_error("Error: Map size does not match the radius specified.");
            return std::nullopt;
        }

        inFile.close();
        return mapData;  // Return loaded map data
    } // loadTileMap

    bool saveTileMap(const TMO::MapData& mapData, const std::string& outputFilePath)
    {
        std::ofstream outFile(outputFilePath);
        if (!outFile.is_open())
        {
            std::cerr << "Error: Could not open file " << outputFilePath << std::endl;
            return false;
        }

        // Save radius, tile shape and orientation
        outFile << "radius:" << mapData.radius << std::endl;
        outFile << "tileShape:" << mapData.tileShape << std::endl;
        outFile << "tileOrientation:" << mapData.tileOrientation << std::endl;

        // Save map
        for (const auto& row : mapData.map)
        {
            bool first = true;
            for (const auto& tile : row)
            {
                if (!first)
                {
                    outFile << ",";
                }
                if (tile.landscape == TMO::Landscape::Mountain)
                {
                    outFile << MountainCharacter;
                }
                else if (tile.landscape == TMO::Landscape::Grassland)
                {
                    outFile << GrasslandCharacter;
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
        return true;  // Indicate successful saving
    } // saveTileMap
} // namespace TileMapIO