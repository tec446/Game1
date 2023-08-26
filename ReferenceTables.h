#pragma once

#include<utility>
#include<array>
#include<vector>
#include<stdexcept>
#include<unordered_map>

#include "Tile.h"

namespace TileMap::ReferenceTables
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
        None,
    };

    using DirectionTable = std::vector<std::pair<Direction, Coordinates>>;
    using NoveltyMap     = std::unordered_map<Direction, DirectionTable>;
    using OffsetMap      = std::unordered_map<Direction, Coordinates>;
    using DirectionMap   = std::unordered_map<Coordinates, Direction, HashCoordinates>;

    const bool getReferenceMaps(const TileShape tileShape, DirectionTable const*& directionTable, NoveltyMap const*& noveltyMap, OffsetMap const*& activeOffset, DirectionMap const*& activeDirections);
    const Coordinates& getOffset(Direction direction, TileShape tileShape);
    const Direction& getDirection(Coordinates coordinates, TileShape tileShape);

#pragma region Square
    //////////////////////// - Square - ////////////////////////////////////
        // Coordinate offsets for each direction on a square map
    static const Coordinates SquareCoordinatesNorthWest { -1, -1 };
    static const Coordinates SquareCoordinatesNorth     { +0, -1 };
    static const Coordinates SquareCoordinatesNorthEast { +1, -1 };
    static const Coordinates SquareCoordinatesEast      { +1, +0 };
    static const Coordinates SquareCoordinatesSouthEast { +1, +1 };
    static const Coordinates SquareCoordinatesSouth     { +0, +1 };
    static const Coordinates SquareCoordinatesSouthWest { -1, +1 };
    static const Coordinates SquareCoordinatesWest      { -1, +0 };
    // Direction paired with their Offset
    static const std::pair<Direction, Coordinates> SquareNorthWest {NorthWest, SquareCoordinatesNorthWest};
    static const std::pair<Direction, Coordinates> SquareNorth     {North, SquareCoordinatesNorth    };
    static const std::pair<Direction, Coordinates> SquareNorthEast {NorthEast, SquareCoordinatesNorthEast};
    static const std::pair<Direction, Coordinates> SquareEast      {East, SquareCoordinatesEast     };
    static const std::pair<Direction, Coordinates> SquareSouthEast {SouthEast, SquareCoordinatesSouthEast};
    static const std::pair<Direction, Coordinates> SquareSouth     {South, SquareCoordinatesSouth    };
    static const std::pair<Direction, Coordinates> SquareSouthWest {SouthWest, SquareCoordinatesSouthWest};
    static const std::pair<Direction, Coordinates> SquareWest      {West, SquareCoordinatesWest     };
    // Container of all directions and their offsets
    static const DirectionTable SquareDirectionTable
    {
        SquareNorthWest,
            SquareNorth,
            SquareNorthEast,
            SquareEast,
            SquareSouthEast,
            SquareSouth,
            SquareSouthWest,
            SquareWest
    };
    // Single Direction to single Coordinates
    static const OffsetMap SquareDirectionToCoordinatesMap
    {
        { NorthWest, SquareCoordinatesNorthWest},
        { North,     SquareCoordinatesNorth },
        { NorthEast, SquareCoordinatesNorthEast },
        { East,      SquareCoordinatesEast },
        { SouthEast, SquareCoordinatesSouthEast },
        { South,     SquareCoordinatesSouth },
        { SouthWest, SquareCoordinatesSouthWest },
        { West,      SquareCoordinatesWest }
    };
    // Single Coordinates to single Direction
    static const DirectionMap SquareCoordinatesToactiveDirections
    {
        { SquareCoordinatesNorthWest, NorthWest },
        { SquareCoordinatesNorth,     North },
        { SquareCoordinatesNorthEast, NorthEast },
        { SquareCoordinatesEast,      East },
        { SquareCoordinatesSouthEast, SouthEast },
        { SquareCoordinatesSouth,     South },
        { SquareCoordinatesSouthWest, SouthWest },
        { SquareCoordinatesWest,      West }
    };
    // Novelty map contains all tiles which were previously non-adjacent before a one tile movement in a Direction
    static const NoveltyMap SquareNoveltyMap
    {
        { Direction::NorthWest, { SquareSouthWest, SquareWest,  SquareNorthWest, SquareNorth, SquareNorthEast }},
        { Direction::North,     { SquareNorthWest, SquareNorth, SquareNorthEast } },
        { Direction::NorthEast, { SquareNorthWest, SquareNorth, SquareNorthEast, SquareEast, SquareSouthEast } },
        { Direction::East,      { SquareNorthEast, SquareEast,  SquareSouthEast } },
        { Direction::SouthEast, { SquareNorthEast, SquareEast,  SquareSouthEast, SquareSouth, SquareSouthWest } },
        { Direction::South,     { SquareSouthEast, SquareSouth, SquareSouthWest } },
        { Direction::SouthWest, { SquareSouthEast, SquareSouth, SquareSouthWest, SquareWest, SquareNorthWest } },
        { Direction::West,      { SquareSouthWest, SquareWest,  SquareNorthWest} }
    };
    //////////////////////// - Square - ////////////////////////////////////
#pragma endregion
<<<<<<< Updated upstream
#pragma region Hexagon
    ////////////////////////// - Hexagon - /////////////////////////////////
    // Coordinate offsets for each direction on a Hexagon map
    static const Coordinates HexagonCoordinatesNorthWest { +0, -1 };
    static const Coordinates HexagonCoordinatesNorthEast { +1, -1 };
    static const Coordinates HexagonCoordinatesEast      { +1, +0 };
    static const Coordinates HexagonCoordinatesSouthEast { +0, +1 };
    static const Coordinates HexagonCoordinatesSouthWest { -1, +1 };
    static const Coordinates HexagonCoordinatesWest      { -1, +0 };
    // Direction paired with their Offset
    static const std::pair<Direction, Coordinates> HexagonNorthWest {NorthWest, HexagonCoordinatesNorthWest};
    static const std::pair<Direction, Coordinates> HexagonNorthEast {NorthEast, HexagonCoordinatesNorthEast};
    static const std::pair<Direction, Coordinates> HexagonEast      {East,      HexagonCoordinatesEast};
    static const std::pair<Direction, Coordinates> HexagonSouthEast {SouthEast, HexagonCoordinatesSouthEast};
    static const std::pair<Direction, Coordinates> HexagonSouthWest {SouthWest, HexagonCoordinatesSouthWest};
    static const std::pair<Direction, Coordinates> HexagonWest      {West,      HexagonCoordinatesWest};
=======
#pragma region Hex
////////////////////////// - Hex - /////////////////////////////////
// Coordinate offsets for each direction on a Hex map
    static const Coordinates HexCoordinatesNorthWest { +0, -1 };
    static const Coordinates HexCoordinatesNorthEast { +1, -1 };
    static const Coordinates HexCoordinatesEast      { +1, +0 };
    static const Coordinates HexCoordinatesSouthEast { +0, +1 };
    static const Coordinates HexCoordinatesSouthWest { -1, +1 };
    static const Coordinates HexCoordinatesWest      { -1, +0 };
    // Direction paired with their Offset
    static const std::pair<Direction, Coordinates> HexNorthWest {NorthWest, HexCoordinatesNorthWest};
    static const std::pair<Direction, Coordinates> HexNorthEast {NorthEast, HexCoordinatesNorthEast};
    static const std::pair<Direction, Coordinates> HexEast      {East, HexCoordinatesEast};
    static const std::pair<Direction, Coordinates> HexSouthEast {SouthEast, HexCoordinatesSouthEast};
    static const std::pair<Direction, Coordinates> HexSouthWest {SouthWest, HexCoordinatesSouthWest};
    static const std::pair<Direction, Coordinates> HexWest      {West, HexCoordinatesWest};
>>>>>>> Stashed changes
    // Container of all directions and their offsets
    static const DirectionTable HexagonDirectionTable
    {
<<<<<<< Updated upstream
        HexagonNorthWest,
        HexagonNorthEast,
        HexagonEast,
        HexagonSouthWest,
        HexagonSouthEast,
        HexagonWest
=======
        HexNorthWest,
            HexNorthEast,
            HexEast,
            HexSouthWest,
            HexSouthEast,
            HexWest
>>>>>>> Stashed changes
    };
    // Single Direction to single Coordinates
    static const OffsetMap HexagonDirectionToCoordinatesMap
    {
<<<<<<< Updated upstream
        { NorthWest, HexagonCoordinatesNorthWest },
        { NorthEast, HexagonCoordinatesNorthEast },
        { East,      HexagonCoordinatesEast      },
        { SouthEast, HexagonCoordinatesSouthEast },
        { SouthWest, HexagonCoordinatesSouthWest },
        { West,      HexagonCoordinatesWest      }
=======
        { NorthWest, HexCoordinatesNorthWest },
        { NorthEast, HexCoordinatesNorthEast },
        { East,      HexCoordinatesEast },
        { SouthEast, HexCoordinatesSouthEast },
        { SouthWest, HexCoordinatesSouthWest },
        { West,      HexCoordinatesWest }
>>>>>>> Stashed changes
    };
    // Single Coordinates to single Direction
    static const DirectionMap HexagonCoordinatesToactiveDirections
    {
        { HexagonCoordinatesNorthWest, NorthWest },
        { HexagonCoordinatesNorthEast, NorthEast },
        { HexagonCoordinatesEast,      East },
        { HexagonCoordinatesSouthEast, SouthEast },
        { HexagonCoordinatesSouthWest, SouthWest },
        { HexagonCoordinatesWest,      West }
    };
    // Novelty map contains all tiles which were previously non-adjacent before a one tile movement in a Direction
    static const NoveltyMap HexagonNoveltyMap
    {
        { NorthWest, { HexagonWest, HexagonNorthWest, HexagonNorthEast } },
        { NorthEast, { HexagonNorthWest, HexagonNorthEast, HexagonEast } },
        { East,      { HexagonNorthEast, HexagonEast, HexagonSouthEast } },
        { SouthEast, { HexagonEast, HexagonSouthEast, HexagonSouthWest } },
        { SouthWest, { HexagonSouthEast, HexagonSouthWest, HexagonWest } },
        { West,      { HexagonSouthWest, HexagonWest, HexagonNorthWest } }
    };
    ////////////////////////// - Hexagon - /////////////////////////////////
#pragma endregion
} // namespace TileMap::ReferenceTables