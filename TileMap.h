#pragma once

#include <vector>
#include <iostream>
#include <memory>
#include <utility>

#include "TileMapObjects.h"
#include "TileMapGenerator.h"
#include "TileMapAStar.h"
#include "TileMapIO.h"

class TileMap
{
public:
	TileMapAStar m_aStar{};
	std::unique_ptr<TMO::MapData> m_activeMapData{ nullptr };

	TileMap();
	void generateMap();
	void loadMap(const std::string& filePath);
	void saveMap(const std::string& filePath);
	void generateAStarMap();
	void printMap(const TMO::coordinatePath& path = TMO::coordinatePath()) const;
	std::vector<TMO::Coordinates> findPath(const TMO::Coordinates start, const TMO::Coordinates destination);


private:

	void setActiveKey();
	// TODO: refactor print functions into a single function
	void printHexagonMap();
	void printSquareMap(const TMO::coordinatePath& path = TMO::coordinatePath()) const;
	void printTriangleMap();

};

