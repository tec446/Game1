#include "MapData.h"

namespace TileMap {
	// Constructor
	MapData::MapData(const TileShape tileShape, const int16_t radius) :
		m_tileShape(tileShape), m_radius(radius)
	{
		setReferenceTables();
	}
	// Copy constructor
	MapData::MapData(const MapData& other) :
		m_tiles(other.m_tiles),
		m_directionTable(other.m_directionTable),
		m_noveltyMap(other.m_noveltyMap),
		m_offsetMap(other.m_offsetMap),
		m_directionMap(other.m_directionMap),
		m_tileShape(other.m_tileShape),
		m_radius(other.m_radius)
	{} // ^ Copy Constructor ^
	// Copy assignment operator
	MapData& MapData::operator=(const MapData& other)
	{
		if (this != &other) // Protect against self-assignment
		{
			m_tiles			 = other.m_tiles;
			m_directionTable = other.m_directionTable;
			m_noveltyMap	 = other.m_noveltyMap;
			m_offsetMap		 = other.m_offsetMap;
			m_directionMap	 = other.m_directionMap;
			m_tileShape		 = other.m_tileShape;
			m_radius		 = other.m_radius;
		}
		return *this;
	} // ^ operator= ^

	// Getters //

	auto MapData::getTiles() const -> const MapTiles&
	{ return m_tiles; }
	auto MapData::getDirectionTable() const -> const ReferenceTables::DirectionTable&
	{ return *m_directionTable; }
	auto MapData::getNoveltyMap() const -> const ReferenceTables::NoveltyMap&
	{ return *m_noveltyMap; }
	auto MapData::getOffsetMap() const -> const ReferenceTables::OffsetMap&
	{ return *m_offsetMap; }
	auto MapData::getDirectionMap() const -> const ReferenceTables::DirectionMap&
	{ return *m_directionMap; }
	auto MapData::getTileShape() const -> const TileShape&
	{ return m_tileShape; }
	auto MapData::getRadius() const -> const int16_t
	{ return m_radius; }

	// Setters //
	void MapData::setMap(const MapTiles& map)
	{ m_tiles = map; }

	// Returns false is any of the reference tables are unassigned
	bool MapData::hasReferenceTables() const
	{
		return m_noveltyMap != nullptr && m_directionTable != nullptr && m_offsetMap != nullptr && m_directionMap != nullptr;
	} // ^ validReferences ^

	// Tells MapData to find the correct reference tables
	void MapData::setReferenceTables()
	{
		if (!getReferenceMaps(m_tileShape, m_directionTable, m_noveltyMap, m_offsetMap, m_directionMap))
		{
			throw std::runtime_error("Failed to set active tables!");
		}
	} // ^ setReferenceTables ^

	// Checks if the Tile.landscape is walkable
	// Uses getTile which validates the coordinates
	bool MapData::isWalkable(const Coordinates& coordinates) const
	{
		const auto tile = getTile(coordinates);
		if (tile == nullptr) { return false; }
		else 
		{
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
		}
	} // ^ isWalkable ^

} // namespace TileMap
