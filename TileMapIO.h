#pragma once

#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <optional>
#include "TileMapObjects.h"

namespace TileMapIO
{
    const char FileExtension[] = ".txt";
    const char MountainCharacter = 'x';
    const char GrasslandCharacter = '.';

    std::optional<TMO::MapData> loadTileMap(const std::string& inputFilePath);
    bool saveTileMap(const TMO::MapData& mapData, const std::string& outputFilePath);
}

