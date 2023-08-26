#pragma once

#include <stdexcept>
#include <vector>
#include <memory>
<<<<<<< Updated upstream
#include <optional>
=======
#include <unordered_map>
>>>>>>> Stashed changes

#include "Tile.h"
#include "ReferenceTables.h"
#include "PathfinderTypes.h"

namespace TileMap 
{
<<<<<<< Updated upstream
struct MapData;

using Map = std::vector<std::vector<Tile>>;

struct MapData
{
	Map				      map{};			// Contains Tiles
	DirectionTable const* directionTable{};	// Contains all Directions and Offsets, Same Format as any value in NoveltyMap.at(Direction)
	NoveltyMap     const* noveltyMap{};		// Contains all novel Directions and Offsets after a one tile movement
	OffsetMap	   const* offsetMap{};		// Direction to Offset
	DirectionMap   const* directionMap{};	// Offset to Direction
	TileShape tileShape{ TileShape::TileShape_None };
	int16_t radius{ 0 };

	MapData() = default;
	// Copy constructor
	MapData(const MapData& other) : 
		map           { other.map			 },
		directionTable{ other.directionTable },
		noveltyMap    { other.noveltyMap	 },
		offsetMap     { other.offsetMap		 },
		directionMap  { other.directionMap	 },
		tileShape     { other.tileShape		 },
		radius        { other.radius		 }	
	{} // ^ copy constructor ^
	// Copy assignment operator
	MapData& operator=(const MapData& other)
	{
		if (this != &other) // Protect against self-assignment
		{
			map			   = other.map;
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
=======
	using MapTiles      = std::vector<std::vector<Tile>>;
	using MapTilesAStar = std::vector<std::vector<Pathfinder::PathNode>>;

	/// MapData
	///   Stores the map Tiles
	///   Stores low resolution maps for pathfinding
	///   Has functionality for interacting with the maps
	class MapData // Abstract Base Class
	{
	protected:
		ReferenceTables::DirectionTable	const* m_directionTable{};	// Contains all Directions and Offsets
		ReferenceTables::NoveltyMap		const* m_noveltyMap{};		// Contains all novel Directions and Offsets after a one tile movement
		ReferenceTables::OffsetMap		const* m_offsetMap{};		// Direction to Offset
		ReferenceTables::DirectionMap	const* m_directionMap{};	// Offset to Direction
		MapTiles  m_tiles{};			
		TileShape m_tileShape{ TileShape::TileShape_None };
		int16_t	  m_radius{ 0 };

		void setReferenceTables();
	public:

		MapData(const TileShape tileShape, const int16_t radius);
		MapData(const MapData& other);
		virtual ~MapData() = default;

		MapData& operator=(const MapData& other);

		auto getDirectionTable() const -> const ReferenceTables::DirectionTable&;
		auto getNoveltyMap()	 const -> const ReferenceTables::NoveltyMap&;
		auto getOffsetMap()	     const -> const ReferenceTables::OffsetMap&;
		auto getDirectionMap()   const -> const ReferenceTables::DirectionMap&;
		auto getTiles()		     const -> const MapTiles&;
		auto getTileShape()	     const -> const TileShape&;
		auto getRadius()		 const -> const int16_t;

		void setMap(const MapTiles& map);

		bool hasReferenceTables() const;
		bool isWalkable(const Coordinates& coordinates) const;

		virtual auto getLowResMap() const -> const std::shared_ptr<const MapData> = 0;
		virtual auto getTile(const Coordinates& coordinates) const -> const Tile* = 0;
		virtual void generateLowResMap() = 0;
		virtual bool isValid(const Coordinates& coordinates) const = 0;
		virtual int  calcMinMoveCost(const Coordinates& from, const Coordinates& to) const = 0;
		virtual auto coordinatesToIndices(const Coordinates& coordinates) const -> Coordinates = 0;
	}; // ^ MapData ^
>>>>>>> Stashed changes

	bool isValid(const Coordinates coordinates) const
	{
		switch (tileShape)
		{
		case TileShape::Square:
			if (coordinates.x < -radius || coordinates.x > radius)
				return false;
			if (coordinates.y < -radius || coordinates.y > radius)
				return false;
			break;
		default:
			throw std::runtime_error("Invalid TileShape!");
		}

		return true;
	} // ^ isValid ^

	bool isWalkable(const Coordinates coordinates) const
	{
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

	const Tile const* getTileByAxialCoordinates(const Coordinates& coordinates) const 
	{
		int xIndex{ 0 };
		int yIndex{ 0 };

		xIndex = coordinates.x + radius;
		yIndex = coordinates.y + radius;
		if (coordinates.y < 0) xIndex += coordinates.y;

		if (yIndex < 0 || yIndex >= map.size())			{ return nullptr; }
		if (xIndex < 0 || xIndex >= map[yIndex].size()) { return nullptr; }

		return &map[yIndex][xIndex];
	} // ^ getTileByAxialCoordinates ^

	const Tile const* getTile(const Coordinates& coordinates) const
	{
		switch (tileShape)
		{
			case TileShape::Square:
				if (!isValid(coordinates)) { return nullptr; }
				return &map[coordinates.y + radius][coordinates.x + radius];
			case TileShape::Hexagon:
				return(getTileByAxialCoordinates(coordinates));
			default:
				throw std::runtime_error("Unknown tile orientation!");
		}
	} // ^ getTile ^
	// TODO: needs differentiated from getMinimumMoveSteps
	int getMinimumMoveCost(const Coordinates& from, const Coordinates& to) const
	{
		switch (tileShape)
		{
		case TileShape::Square:
			return(calculateSquareDistance(from, to));
		case TileShape::Hexagon:
			return(calculateAxialDistance(from, to));
		default:
			throw std::runtime_error("Unknown tile orientation!");
		}
	} // ^ getMinimumMoveCost ^
	
	int getMinimumMoveSteps(const Coordinates& from, const Coordinates& to) const
	{

		switch (tileShape)
		{
		case TileShape::Square:
			return(calculateSquareDistance(from, to));
		case TileShape::Hexagon:
			return(calculateAxialDistance(from, to));
		default:
			throw std::runtime_error("Unknown tile orientation!");
		}
	} // ^ getMinimumMoveSteps ^
	int calculateSquareDistance(const Coordinates& from, const Coordinates& to) const
	{
		int dx = abs(to.x - from.x);
		int dy = abs(to.y - from.y);
		int totalDistance{ 0 };
		int min, max;

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
	}
	int calculateAxialDistance(const Coordinates& from, const Coordinates& to) const
	{
		int fromZ = (-from.x - from.y);
		int toZ   = (-to.x   - to.y);
		// Axial Coordinates Distance ( (x + y + z) / 2 ) * minimum cost
		return((((abs(from.x - to.x) + abs(from.y - to.y) + abs(fromZ - toZ)) / 2) * 10));
	};
}; // MapData

} // namespace TileMap