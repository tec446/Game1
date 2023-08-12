#include "SquareMapData.h"

namespace TileMap 
{
// Constructor
SquareMapData::SquareMapData(TileShape tileShape, int16_t radius) : MapData(tileShape, radius)
{ }

// Returns a pointer to the Tile
// Validates the Coordinates
const Tile* SquareMapData::getTile(const Coordinates& coordinates) const
{
	if (!isValid(coordinates)) { return nullptr; }
	return &m_map[coordinates.y + m_radius][coordinates.x + m_radius];
} // ^ getTile ^

bool SquareMapData::isValid(const Coordinates coordinates) const
{
	return !(coordinates.x < -m_radius ||
			 coordinates.x >  m_radius ||
			 coordinates.y < -m_radius ||
			 coordinates.y >  m_radius);
} // ^ isValid ^

// Calculates the minimum movement cost between two Tiles, assuming a straight line & no obstacles
// Assumes Valid Coordinates
int SquareMapData::calcMinMoveCost(const Coordinates& from, const Coordinates& to) const
{
	int dx = abs(to.x - from.x);
	int dy = abs(to.y - from.y);
	int totalDistance{ 0 };
	// min = lesser  absolute value = number of diagonal moves
	// max = greater absolute value
	//					(max - min) = number of cardinal moves
	int min, max;

	if (dx > dy) {
		min = dy;
		max = dx;
	}
	else {
		min = dx;
		max = dy;
	}
	totalDistance += (min * 14);		// Diagonal movement costs 14
	totalDistance += ((max - min) * 10);// Cardinal movement costs 10
	return totalDistance;
} // ^ calcMinMoveCost ^

// Converts Coordinates to the indices of the Tile in the Map
Coordinates SquareMapData::coordinatesToIndices(const Coordinates& coordinates) const
{
	Coordinates indices;
	indices.x = coordinates.x + m_radius;
	indices.y = coordinates.y + m_radius;
	return indices;
} // ^ coordinatesToIndices ^

} // namespace TileMap
