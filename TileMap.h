#pragma once

#include <vector>
#include <iostream>
#include <memory>
#include <utility>

#include "MapData.h"
#include "IO.h"
#include "AStar.h"

namespace TileMap
{
	class TileMap
	{
	public:
		std::unique_ptr<MapData> m_activeMapData{ nullptr };
	private:
	};
}