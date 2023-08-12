#pragma once

#include <stdexcept>
#include <vector>
#include <memory>

#include "Tile.h"
#include "ReferenceTables.h"

namespace TileMap
{
	using Map = std::vector<std::vector<Tile>>;

	class MapData // Abstract Base Class
	{
	protected:
		Map					   m_map{};				// Contains Tiles
		DirectionTable	const* m_directionTable{};	// Contains all Directions and Offsets
		NoveltyMap		const* m_noveltyMap{};		// Contains all novel Directions and Offsets after a one tile movement
		OffsetMap		const* m_offsetMap{};		// Direction to Offset
		DirectionMap	const* m_directionMap{};	// Offset to Direction
		TileShape			   m_tileShape{ TileShape::TileShape_None };
		int16_t				   m_radius{ 0 };

		void setReferenceTables();
	public:
		// Constructors / Destructors
		MapData(const TileShape tileShape, const int16_t radius);
		MapData(const MapData& other);
		virtual ~MapData() = default;
		// Operators
		MapData& operator=(const MapData& other);
		// Getters
		const Map&			  getMap()			  const;
		const DirectionTable& getDirectionTable() const;
		const NoveltyMap&	  getNoveltyMap()	  const;
		const OffsetMap&	  getOffsetMap()	  const;
		const DirectionMap&	  getDirectionMap()	  const;
		const TileShape&	  getTileShape()	  const;
		const int16_t		  getRadius()		  const;
		// Setters
		void setMap(const Map& map);
		// Queries
		bool hasReferenceTables() const;
		bool isWalkable(const Coordinates& coordinates) const;
		// Virtual functions
		virtual bool isValid(const Coordinates coordinates) const = 0;
		virtual const Tile* getTile(const Coordinates& coordinates) const = 0;
		virtual int calcMinMoveCost(const Coordinates& from, const Coordinates& to) const = 0;
		virtual Coordinates coordinatesToIndices(const Coordinates& coordinates) const = 0;
	}; // ^ MapData ^

} // ^ namespace TileMap ^
