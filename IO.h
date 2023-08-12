#pragma once

#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <optional>
#include <vector>
#include <cstdint>
#include <memory>
#include <windows.h>

#include "Tile.h"
#include "MapData.h"
#include "StringConversions.h"
#include "MapGenerator.h"

namespace TileMap
{
    const char FileExtension[] = ".txt";
    const char SaveFolder[] = "Maps/";
    const char MountainCharacter = 'x';
    const char GrasslandCharacter = '.';

    // loadTileMap // Loads from a txt file
    std::unique_ptr<MapData> loadMap(const std::string& fileName);

    void printMap(const MapData& mapData, const std::vector<Coordinates>& path = {});
    void printSquareMap(const MapData& mapData, const std::vector<Coordinates>& path = {});
    void printHexMap(const MapData& mapData, const std::vector<Coordinates>& path = {});
}