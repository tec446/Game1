#pragma once

#include <memory>

#include "Tile.h"
#include "MapData.h"
#include "SquareMapData.h"
//#include "HexMapData.h"

namespace TileMap
{
	std::unique_ptr<MapData> generateMapData(TileShape tileShape, int16_t radius);

} // namespace TileMap