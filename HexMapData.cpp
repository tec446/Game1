#include "HexMapData.h"

namespace TileMap
{
// Constructor
HexMapData::HexMapData(TileShape tileShape, int16_t radius) : MapData(tileShape, radius)
{}

// Returns a pointer to the Tile
// Validates the Coordinates
const Tile* HexMapData::getTile(const Coordinates& coordinates) const
{
	Coordinates indices = coordinatesToIndices(coordinates);
	if (!areValidIndices(indices)) { return nullptr; }
	else { return &m_map[indices.y][indices.x]; }
} // ^ getTileByAxialCoordinates ^

// - Calculates the minimum movement cost between two Tiles, assuming a straight line & no obstacles
// - Uses Axial Coordinates
// - Assumes Valid Coordinates
int HexMapData::calcMinMoveCost(const Coordinates& from, const Coordinates& to) const
{
	int fromZ = (-from.x - from.y);
	int toZ   = (-to.x   - to.y);
	return((((abs(from.x - to.x) + abs(from.y - to.y) + abs(fromZ - toZ)) / 2) * 10));
} // ^ calculateAxialDistance ^

bool HexMapData::isValid(const Coordinates coordinates) const
{
	Coordinates indices = coordinatesToIndices(coordinates);
	return (areValidIndices(indices) );
} // ^ isValid ^

// Converts Axial Coordinates to the indices of the Tile in the Map
Coordinates HexMapData::coordinatesToIndices(const Coordinates& coordinates) const
{
	Coordinates indices;
	indices.x = coordinates.x + m_radius;
	indices.y = coordinates.y + m_radius;
	if (coordinates.y < 0) indices.x += coordinates.y;

	return indices;
} // ^ coordinatesToIndices ^

bool HexMapData::areValidIndices(const Coordinates& indices) const
{
	if (indices.y < 0 || indices.y >= m_map.size())			   { return false; }
	if (indices.x < 0 || indices.x >= m_map[indices.y].size()) { return false; }
	return true;
} // ^ areValidIndices ^

} // namespace TileMap