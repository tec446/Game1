#include "SquareMapData.h"

namespace TileMap 
{
// Returns a pointer to the Tile
// Validates the Coordinates
const Tile* SquareMapData::getTile(const Coordinates& coordinates) const
{
	if (!isValid(coordinates)) { return nullptr; }
	return &m_tiles[coordinates.y + m_radius][coordinates.x + m_radius];
} // ^ getTile ^

const std::shared_ptr<const MapData> SquareMapData::getLowResMap() const
{
	return(m_lowResMap);
} // ^ getLowResMap ^

bool SquareMapData::isValid(const Coordinates& coordinates) const
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

// Converts Coordinates to the indices of the Tile in the MapTiles
Coordinates SquareMapData::coordinatesToIndices(const Coordinates& coordinates) const
{
	Coordinates indices;
	indices.x = coordinates.x + m_radius;
	indices.y = coordinates.y + m_radius;
	return indices;
} // ^ coordinatesToIndices ^



void SquareMapData::generateLowResMap() 
{
	
	const Coordinates northWestOffset{ 0, 1 };
	const Coordinates northEastOffset{ 1, 1 };
	const Coordinates southWestOffset{ 0, 0 };
	const Coordinates southEastOffset{ 1, 0 };

    int lowResRadius = (m_radius) / 2; // MetaTile size is 2x2, so half the radius
	if (m_radius % 2 == 1) { lowResRadius += 1; } // If the radius is odd, round up
    int lowResSize = 2 * lowResRadius + 1; // Diameter of the low-res map
	Coordinates newIndicies{};

	//auto newMapData = std::make_unique<SquareMapDataAStar>(m_tileShape, lowResRadius);
	SquareMapDataAStar newMapData(m_tileShape, lowResRadius);
	// Create the low-res map
	std::vector<std::vector<SquareMetaTile>> lowResTiles(lowResSize, std::vector<SquareMetaTile>(lowResSize));

    for (int16_t y = -lowResRadius; y <= lowResRadius; ++y) {
        for (int16_t x = -lowResRadius; x <= lowResRadius; ++x) {
			newIndicies = newMapData.coordinatesToIndices(Coordinates{ x, y });
			SquareMetaTile& nextTile = lowResTiles[newIndicies.y][newIndicies.x];
			nextTile.northWest = getTile(Coordinates{ x * 2, y * 2 } + northWestOffset);
			nextTile.northEast = getTile(Coordinates{ x * 2, y * 2 } + northEastOffset);
			nextTile.southWest = getTile(Coordinates{ x * 2, y * 2 } + southWestOffset);
			nextTile.southEast = getTile(Coordinates{ x * 2, y * 2 } + southEastOffset);
			nextTile.coordinates = Coordinates{ x, y };
			nextTile.ID = HashCoordinates()(Coordinates{ x, y });
        }
    }

	newMapData.setMap(lowResTiles);

	m_lowResMap.reset(new SquareMapDataAStar(std::move(newMapData)));

} // ^ generateLowResMap ^

void SquareMapDataAStar::setMap(const std::vector<std::vector<SquareMetaTile>>& map) { m_tiles = map; }

} // namespace TileMap
