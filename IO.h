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

namespace TileMap
{
    const char FileExtension[] = ".txt";
    const char SaveFolder[] = "Maps/";
    const char MountainCharacter = 'x';
    const char GrasslandCharacter = '.';

    // loadTileMap // Loads from a txt file
    std::optional<MapData> loadMap(const std::string& fileName);
    std::optional<MapData> loadHexagonMap(const std::string& fileName);
    // saveTileMap // Saves to   a txt file
    bool saveMap(const MapData& mapData, const std::string& fileName);

    void printMap(const MapData& mapData, const std::vector<Coordinates>& path = {});
    void printSquareMap(const MapData& mapData, const std::vector<Coordinates>& path = {});
    void printHexagonMap(const MapData& mapData, const std::vector<Coordinates>& path = {});
}