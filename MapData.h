#pragma once

#include <stdexcept>
#include <vector>
#include <memory>

#include "Tile.h"
#include "ReferenceTables.h"

namespace TileMap 
{
struct MapData;

using Map = std::vector<std::vector<Tile>>;

struct MapData
{
	std::unique_ptr<Map> map{};				// Contains Tiles
	DirectionTable const* directionTable{};	// Contains all Directions and Offsets, Same Format as any value in NoveltyMap.at(Direction)
	NoveltyMap     const* noveltyMap{};		// Contains all novel Directions and Offsets after a one tile movement
	OffsetMap	   const* offsetMap{};		// Direction to Offset
	DirectionMap   const* directionMap{};	// Offset to Direction
	TileShape tileShape{ TileShape::Square };
	int radius{ 0 };

	MapData() = default;
	// Copy constructor
	MapData(const MapData& other) : 
		map           { std::make_unique<Map>(*other.map) },
		directionTable{ other.directionTable			 },
		noveltyMap    { other.noveltyMap					 },
		offsetMap     { other.offsetMap					 },
		directionMap  { other.directionMap				 },
		tileShape     { other.tileShape					 },
		radius        { other.radius						 }	
	{} // ^ copy constructor ^
	// Copy assignment operator
	MapData& operator=(const MapData& other)
	{
		if (this != &other) // Protect against self-assignment
		{
			map			   = std::make_unique<Map>(*other.map);
			directionTable = other.directionTable;
			noveltyMap	   = other.noveltyMap;
			offsetMap	   = other.offsetMap;
			directionMap   = other.directionMap;
			tileShape	   = other.tileShape;
			radius		   = other.radius;
		}
		return *this;
	} // ^ copy assignment operator ^

	bool validReferences () const
	{
		if (noveltyMap != nullptr && directionTable != nullptr && offsetMap != nullptr && directionMap != nullptr) { return true; }
		else return false;
	}
	void setActiveReferenceMaps()
	{
		if (!getReferenceMaps(tileShape, directionTable, noveltyMap, offsetMap, directionMap))
		{
			throw std::runtime_error("Failed to set active tables!");
		}
	} // setActiveTables

	bool isValid(const Coordinates coordinates) const
	{
		
		if (coordinates.x < -radius || coordinates.x > radius)
			return false;
		if (coordinates.y < -radius || coordinates.y > radius)
			return false;
		
		return true;
	} // ^ isValid ^

	bool isWalkable(const Coordinates coordinates) const
	{
		// getTile validates coordinates
		const auto tile = getTile(coordinates);
		if (tile == nullptr) { return false; }

		Landscape landscape = tile->landscape;
		switch (landscape)
		{
		case Landscape::Coast:		return false;
		case Landscape::Ocean:		return false;
		case Landscape::Grassland:	return true;
		case Landscape::Forest:		return true;
		case Landscape::Hill:		return true;
		case Landscape::Mountain:	return false;
		default:					return false;
		}
	} // ^ isWalkable ^
	
	const Tile* getTile(const Coordinates& coordinates) const
	{
		if (!isValid(coordinates)) { return nullptr; }
		return &(*map)[coordinates.y + radius][coordinates.x + radius];
	} // ^ getTile ^
	
	int getMinimumMoveCost(const Coordinates& from, const Coordinates& to) const
	{
		int dx = abs(to.x - from.x);
		int dy = abs(to.y - from.y);
		int totalDistance{ 0 };
		int min, max;

		switch (tileShape)
		{
		case TileShape::Square:
			if (dx > dy)
			{
				min = dy;
				max = dx;
			}
			else
			{
				min = dx;
				max = dy;
			}
			totalDistance += (min * 14);		// diagonal movement costing x14
			totalDistance += ((max - min) * 10);// horizontal and vertical movement costing x10
			return totalDistance;
		default:
			throw std::runtime_error("Unknown tile orientation!");
		}
	} // ^ getMinimumMoveCost ^

	int getMinimumMoveSteps(const Coordinates& from, const Coordinates& to) const
	{
		int dx = abs(to.x - from.x);
		int dy = abs(to.y - from.y);
		int totalDistance{ 0 };
		int min, max;

		switch (tileShape)
		{
		case TileShape::Square:
			if (dx > dy)
			{
				min = dy;
				max = dx;
			}
			else
			{
				min = dx;
				max = dy;
			}
			totalDistance += (min * 14);		// diagonal movement costing 14
			totalDistance += ((max - min) * 10);// horizontal and vertical movement costing x10
			return totalDistance;
		default:
			throw std::runtime_error("Unknown tile orientation!");
		}
	} // ^ getMinimumMoveSteps ^
}; // MapData

} // namespace TileMap