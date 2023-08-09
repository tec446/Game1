#include <iostream>
#include <stdexcept>
#include <memory>
#include <optional>
#include <vector>

#include "TileMap.h"
#include "ReferenceTables.h"

int main()
{
	TileMap::TileMap tileMap{};


	//const auto opt = TileMap::loadMap("testMap1");
	const auto opt = TileMap::loadHexagonMap("hexagon_testMap1");

	if (!opt.has_value())
	{
		throw std::runtime_error("Error failed to load map!");
	}

	if (tileMap.m_activeMapData == nullptr)
	{
		tileMap.m_activeMapData = std::make_unique<TileMap::MapData>();
	}

	*(tileMap.m_activeMapData) = opt.value();
	std::cout << "Map loaded successfully!" << std::endl;

	tileMap.m_activeMapData->setActiveReferenceMaps();


	const auto mapData = *(tileMap.m_activeMapData);
	const auto map     = &mapData.map;
	
	std::vector<TileMap::Coordinates> path{};
	TileMap::AStar::findPath({-7,0 }, { -5,9 }, mapData, path);
	for (const auto& coord : path)
	{
		std::cout << "\nPath: " << coord;
	}
	TileMap::printMap(mapData, path);
	

	return(0);
}
