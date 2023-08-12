#include "ReferenceTables.h"

namespace TileMap
{
#pragma region getters
    //////////////////////// - Getters - ///////////////////////////////////
    const bool getReferenceMaps(const TileShape tileShape, DirectionTable const*& directionTable, NoveltyMap const*& noveltyMap, OffsetMap const*& activeOffset, DirectionMap const*& activeDirections)
    {
        switch (tileShape)
        {
        case Square:
            directionTable   = &SquareDirectionTable;
            noveltyMap       = &SquareNoveltyMap;
            activeOffset     = &SquareDirectionToCoordinatesMap;
            activeDirections = &SquareCoordinatesToactiveDirections;
            return true;
        case Hex:
            directionTable   = &HexDirectionTable;
			noveltyMap       = &HexNoveltyMap;
			activeOffset     = &HexDirectionToCoordinatesMap;
			activeDirections = &HexCoordinatesToactiveDirections;
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
        case Square:  return SquareDirectionToCoordinatesMap.at(direction);
        case Hex: return HexDirectionToCoordinatesMap.at(direction);
        default:      throw std::runtime_error("Invalid TileShape!");
        }
    } // getDirection single Coordinates to single Direction
    const Direction& getDirection(Coordinates coordinates, TileShape tileShape)
    {
        switch (tileShape)
        {
        case Square:  return SquareCoordinatesToactiveDirections.at(coordinates);
        case Hex: return HexCoordinatesToactiveDirections.at(coordinates);
        default:      throw std::runtime_error("Invalid TileShape!");
        }
    } // getDirection
    //////////////////////// - Getters - ///////////////////////////////////
#pragma endregion
} // namespace TileMap
