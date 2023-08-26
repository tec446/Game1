#pragma once

#include <vector>
#include <iostream>
#include <memory>
#include <utility>

#include "MapData.h"
#include "SquareMapData.h"
//#include "HexMapData.h"
#include "IO.h"
#include "Pathfinder.h"
#include "PathfinderTypes.h"


namespace TileMap
{
	class TileMap
	{
	public:
		std::unique_ptr<MapData> m_activeMapData{ nullptr };
	private:
	};
}