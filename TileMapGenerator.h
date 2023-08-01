#pragma once

#include <vector>
#include <iostream> // for error checking
#include <memory>   // for smart pointers

#include "TilemapObjects.h"

class TileMapGenerator
{
public:
	TileMapGenerator()
	{

	}

	static std::unique_ptr<TMO::MapData> generateMap(TMO::MapCreationData creationData)
	{
		std::unique_ptr<TMO::MapData> mapData = std::make_unique<TMO::MapData>();
		mapData->radius = creationData.radius;
		mapData->tileShape = creationData.tileShape;
		mapData->tileOrientation = creationData.tileOrientation;
		int rows{ creationData.radius * 2 + 1 };
		int columns{ creationData.radius * 2 + 1 };

		switch (creationData.tileShape)
		{
		case TMO::TileShape::Hexagon:
			std::cerr << "\n\tError, Hexagon map not implemented in generateMap!";
			break;
		case TMO::TileShape::Square:
			mapData->map.reserve(rows);  // Reserve memory to avoid reallocations

			for (int row = 0; row < rows; ++row)
			{
				// Create and insert a new row of Tiles
				std::vector<TMO::Tile> tileRow;
				tileRow.reserve(columns);

				for (int column = 0; column < columns; ++column)
				{
					// Create a new Tile
					TMO::Tile tile(TMO::Coordinates(row, column), TMO::Landscape::Grassland);

					// Add it to the row using std::move to avoid copying
					tileRow.push_back(std::move(tile));
				}

				mapData->map.push_back(std::move(tileRow));  // Move the row into the map
			}
			break;
		case TMO::TileShape::Triangle:
			std::cerr << "\n\tError, Trangle map not implemented in generateMap!";
			break;
		default:
			std::cerr << "\n\tError, Unsupported tileShape in generateMap!";
		}





		return(mapData);
	}
private:

};