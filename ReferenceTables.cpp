#include "ReferenceTables.h"

namespace TileMap
{
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
    static const DirectionTable squareDirectionTable
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
    static const OffsetMap squareDirectionToCoordinatesMap
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
    static const DirectionMap squareCoordinatesToactiveDirections
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
    static const NoveltyMap squareNoveltyMap
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
#pragma region getters
//////////////////////// - Getters - ///////////////////////////////////
    const bool getReferenceMaps(const TileShape tileShape, DirectionTable const*& directionTable, NoveltyMap const*& noveltyMap, OffsetMap const*& activeOffset, DirectionMap const*& activeDirections)
    {
        switch (tileShape)
        {
        case Square:
            directionTable   = &squareDirectionTable;
            noveltyMap       = &squareNoveltyMap;
            activeOffset     = &squareDirectionToCoordinatesMap;
            activeDirections = &squareCoordinatesToactiveDirections;
            return true;
        default:
            throw std::runtime_error("Invalid TileShape!");
            return false;
        }
    } // getReferenceMaps
    // getOffset single Direction to single Coordinates
    const Coordinates& getOffset(Direction direction, TileShape tileShape)
    {
        switch (tileShape)
        {
        case Square: return squareDirectionToCoordinatesMap.at(direction);
        default:     throw std::runtime_error("Invalid TileShape!");
        }
    } // getDirection single Coordinates to single Direction
    const Direction& getDirection(Coordinates coordinates, TileShape tileShape)
    {
        switch (tileShape)
        {
        case Square: return squareCoordinatesToactiveDirections.at(coordinates);
        default:     throw std::runtime_error("Invalid TileShape!");
        }
    } // getDirection
//////////////////////// - Getters - ///////////////////////////////////
#pragma endregion
} // namespace TileMap
