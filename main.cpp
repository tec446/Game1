#pragma once

#include <iostream>

#include "TileMap.h"

int main()
{
	TileMap tileMap{};

	//tileMap.generateMap();

	tileMap.loadMap("testMap1");
	//tileMap.loadMap("testMap2");

	tileMap.printMap();
	
	auto tempPtr = tileMap.m_activeMapData.get();

	TMO::coordinatePath path = tileMap.findPath({ -15,-10 }, { +10,+15 });

	std::cout << "\nPath: ";
	for (const auto& coordinate : path)
	{
		std::cout << "\n" << coordinate.x << ", " << coordinate.y;
	}
	tileMap.printMap(path);
	
	return 0;
}