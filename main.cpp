#include <iostream>
#include <stdexcept>
#include <memory>
#include <optional>
#include <vector>

#include "TileMap.h"
#include "ReferenceTables.h"

int main()
{
#pragma region squareMap
	{
		TileMap::TileMap tileMap{};

		tileMap.m_activeMapData = TileMap::loadMap("square_testMap1");

		if (tileMap.m_activeMapData == nullptr) { throw std::runtime_error("Error failed to load map!"); }

		std::cout << "Map loaded successfully!" << std::endl;

		const auto& mapData = *tileMap.m_activeMapData;
		const auto& map = tileMap.m_activeMapData->getMap();

		std::vector<TileMap::Coordinates> path{};
		TileMap::AStar::findPath({ -15,15 }, { 15,15 }, mapData, path);
		for (const auto& coord : path)
		{
			std::cout << "\nPath: " << coord;
		}
		TileMap::printMap(mapData, path);
	}
#pragma endregion
#pragma region squareMap
	{
	TileMap::TileMap tileMap{};

	tileMap.m_activeMapData = TileMap::loadMap("hex_testMap1");

	if (tileMap.m_activeMapData == nullptr) { throw std::runtime_error("Error failed to load map!"); }

	std::cout << "Map loaded successfully!" << std::endl;

	const auto& mapData = *tileMap.m_activeMapData;
	const auto& map = tileMap.m_activeMapData->getMap();

	std::vector<TileMap::Coordinates> path{};
	TileMap::AStar::findPath({ -7,0 }, { -5,9 }, mapData, path);
	for (const auto& coord : path)
	{
		std::cout << "\nPath: " << coord;
	}
	TileMap::printMap(mapData, path);
	}
#pragma endregion

	return(0);
}
