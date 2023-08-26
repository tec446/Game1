#include <iostream>
#include <stdexcept>
#include <memory>
#include <optional>
#include <vector>
#include <chrono>

#include "TileMap.h"
#include "ReferenceTables.h"

int main()
{
<<<<<<< Updated upstream
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
	
=======
#pragma region 
	if(true)
	{
		TileMap::TileMap tileMap{};

		tileMap.m_activeMapData = TileMap::loadMap("square_testMap1");

		if (tileMap.m_activeMapData == nullptr) { throw std::runtime_error("Error failed to load map!"); }

		tileMap.m_activeMapData->generateLowResMap();

		std::cout << "MapTiles loaded successfully!" << std::endl;

		const auto& mapData = *tileMap.m_activeMapData;
		const auto& map = tileMap.m_activeMapData->getTiles();

		std::vector<TileMap::Coordinates> path{};
		
		// chrono test
		int sampleSize = 100000;
		auto start = std::chrono::high_resolution_clock::now();
		for (int x = 0; x < sampleSize; x++)
		{
			TileMap::Pathfinder::AStar::findPath(mapData, { -15,15 }, { 15,15 }, path);
		}
		auto end = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
		
		std::cout << "\nAverage time taken by function: " << duration.count() / sampleSize << " microseconds" << std::endl;
		// chrono test
		std::cout << "";

		/*
		for (const auto& coord : path)
		{
			std::cout << "\nPath: " << coord;
		}
		TileMap::printMap(mapData, path);
		*/
	}
#pragma endregion

>>>>>>> Stashed changes

	return(0);
}
