#pragma once

#include<utility>
#include<array>
#include<vector>
#include<stdexcept>
#include<unordered_map>

#include "Tile.h"

namespace TileMap
{
    enum Direction
    {
        SouthEast,
        SouthSouthEast,
        South,
        SouthSouthWest,
        SouthWest,
        WestSouthWest,
        West,
        WestNorthWest,
        NorthWest,
        NorthNorthWest,
        North,
        NorthNorthEast,
        NorthEast,
        EastNorthEast,
        East,
        EastSouthEast,
        Direction_None,
    };

    using DirectionTable = std::vector<std::pair<Direction, Coordinates>>;
    using NoveltyMap     = std::unordered_map<Direction, DirectionTable>;
    using OffsetMap      = std::unordered_map<Direction, Coordinates>;
    using DirectionMap   = std::unordered_map<Coordinates, Direction, HashCoordinates>;

    const bool getReferenceMaps(const TileShape tileShape, DirectionTable const*& directionTable, NoveltyMap const*& noveltyMap, OffsetMap const*& activeOffset, DirectionMap const*& activeDirections);
    const Coordinates& getOffset(Direction direction, TileShape tileShape);
    const Direction& getDirection(Coordinates coordinates, TileShape tileShape);
}