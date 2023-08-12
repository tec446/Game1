#include "MapGenerator.h"

namespace TileMap
{
	std::unique_ptr<MapData> generateMapData(TileShape tileShape, int16_t radius)
	{
		switch (tileShape)
		{
		case TileShape::Hex:
			return std::unique_ptr<HexMapData>(new HexMapData(tileShape, radius));
			//return std::make_unique<HexMapData>(radius);
		case TileShape::Square:
			return std::make_unique<SquareMapData>(tileShape, radius);
		default:
			throw std::runtime_error("TileShape not recognized");
		}
	} // ^ generateMapData ^
} // namespace TileMap