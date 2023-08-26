#include "MapGenerator.h"

namespace TileMap
{
	// Used to create a new MapData instance
	std::unique_ptr<MapData> generateMapData(TileShape tileShape, int16_t radius)
	{
		switch (tileShape)
		{
		//case TileShape::Hex:
		//	return std::make_unique<HexMapData>(tileShape, radius);
		case TileShape::Square:
			return std::make_unique<SquareMapData>(tileShape, radius);
		default:
			throw std::runtime_error("TileShape not recognized");
		}
	} // ^ generateMapData ^
} // namespace TileMap