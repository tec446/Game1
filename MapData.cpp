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
		m_map(other.m_map),
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
			m_map			 = other.m_map;
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

	const Map& MapData::getMap() const
	{ return m_map; }
	const DirectionTable& MapData::getDirectionTable() const
	{ return *m_directionTable; }
	const NoveltyMap& MapData::getNoveltyMap() const
	{ return *m_noveltyMap; }
	const OffsetMap& MapData::getOffsetMap() const
	{ return *m_offsetMap; }
	const DirectionMap& MapData::getDirectionMap() const
	{ return *m_directionMap; }
	const TileShape& MapData::getTileShape() const
	{ return m_tileShape; }
	const int16_t MapData::getRadius() const
	{ return m_radius; }

	// Setters //
	void MapData::setMap(const Map& map)
	{ m_map = map; }

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
