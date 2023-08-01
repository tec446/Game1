#include "Tilemap.h"
#include "TilemapGenerator.h"

TileMap::TileMap() : m_activeMapData(nullptr)
{

};

void TileMap::printMap(const TMO::coordinatePath& path) const
{
	if (!m_activeMapData)
	{
		throw std::runtime_error("Error, no map data available!");
	}
	switch (m_activeMapData->tileShape)
	{
		case (TMO::TileShape::Hexagon):
			throw std::runtime_error("Error, Hexagon map not implemented in printmap!");
			break;
		case (TMO::TileShape::Square):
			printSquareMap(path);
			break;
		case (TMO::TileShape::Triangle):
			throw std::runtime_error("Error, Triangle map not implemented in printmap!");
			break;
	}

}

void TileMap::printHexagonMap(){}

void TileMap::printSquareMap(const TMO::coordinatePath& path) const
{
	std::cout << "\n__" << std::string(m_activeMapData->map.size() * 4, '_');

	for (const auto& row : m_activeMapData->map)
	{
		std::cout << "\n";
		for (const auto& tile : row)
		{
			// Check if tile is in path
			if (std::find(path.begin(), path.end(), tile.coordinates) != path.end())
			{
				std::cout << " @ "; // Print @ if tile is in path
			}
			else // If tile is not in path, print according to its landscape
			{
				switch (tile.landscape)
				{
				case TMO::Landscape::Grassland:
					std::cout << " . ";
					break;
				case TMO::Landscape::Mountain:
					std::cout << " X ";
					break;
				default:
					std::cout << " ? ";
					break;
				}
			}
		}
	}

	std::cout << "\n__" << std::string(m_activeMapData->map.size() * 4, '_');
}


void TileMap::printTriangleMap() {}

void TileMap::loadMap(const std::string& filePath) 
{
	auto opt = TileMapIO::loadTileMap(filePath);
	if (opt.has_value())
	{
		m_activeMapData = std::make_unique<TMO::MapData>(std::move(*opt));
	}
	else
	{
		throw std::runtime_error("Error, could not load map!");
	}
	// set the map orientation key
	setActiveKey();

}

void TileMap::saveMap(const std::string& filePath)
{
	const auto success = TileMapIO::saveTileMap(*m_activeMapData, filePath);
	if (!success)
	{
		throw std::runtime_error("Error, could not save map!");
	}
}

void TileMap::generateMap()
{
	TMO::MapCreationData mapCreationData{
		mapCreationData.radius			= 10,
		mapCreationData.tileShape		= TMO::TileShape::Square,
		mapCreationData.tileOrientation = TMO::TileOrientation::Square
	};

	// Generates the TileMap and implicitly calls std::move
	m_activeMapData = TileMapGenerator::generateMap(mapCreationData);
	// set the OrientationKey
	m_activeMapData->orientationKey.setActiveKey(mapCreationData.tileOrientation);

}

void TileMap::generateAStarMap()
{
	m_aStar.generateMap(m_activeMapData->map);
}

std::vector<TMO::Coordinates> TileMap::findPath(const TMO::Coordinates start, const TMO::Coordinates destination)
{
	std::vector<TMO::Coordinates> path{};
	m_aStar.findPath(start, destination, *m_activeMapData, path);
	return path;
}

void TileMap::setActiveKey()
{
	m_activeMapData->orientationKey.setActiveKey(m_activeMapData->tileOrientation);
}