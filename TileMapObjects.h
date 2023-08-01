#pragma once

#include <map>
#include <vector>
#include <iostream>
#include <optional>
#include <memory> // for smart pointers

namespace TMO // TMO stands for TilemapObjects
{

	// Forward Declarations
	struct Coordinates;
	struct AStarMetaTile;
	struct Tile;
	struct MapCreationData;
	struct OrientationKey;
	struct MapData;
	struct CoordinateHash;

	// enums
	enum class TileShape
	{
		Square,
		Hexagon,
		Triangle,
	};
	enum class TileOrientation
	{
		Square,
		HexagonNS,
		HexagonEW,
		TriangleStandard,
		TriangleInverted,
	};
	enum class Landscape
	{
		Coast,
		Ocean,
		Grassland,
		Forest,
		Hill,
		Mountain,
		Error,
	};
	enum class Direction
	{
		SouthEast,
		SouthSouthEast,
		South,
		SouthSouthWest,
		SouthWest,
		WestSouthWest,
		West,
		WestNorthWest,
		NorthWest,
		NorthNorthWest,
		North,
		NorthNorthEast,
		NorthEast,
		EastNorthEast,
		East,
		EastSouthEast,
	};
	
	// string conversions
	inline TMO::TileShape stringToTileShape(const std::string& str)
	{
		if (str == "Square")
			return TMO::TileShape::Square;
		else if (str == "Hexagon")
			return TMO::TileShape::Hexagon;
		else if (str == "Triangle")
			return TMO::TileShape::Triangle;
		else
			throw std::invalid_argument("Invalid TileShape string: " + str);

	}
	inline TMO::TileOrientation stringToTileOrientation(const std::string& str)
	{
		if (str == "Square")
			return TMO::TileOrientation::Square;
		else if (str == "HexagonNS")
			return TMO::TileOrientation::HexagonNS;
		else if (str == "HexagonEW")
			return TMO::TileOrientation::HexagonEW;
		else if (str == "TriangleStandard")
			return TMO::TileOrientation::TriangleStandard;
		else if (str == "TriangleInverted")
			return TMO::TileOrientation::TriangleInverted;
		else
			throw std::invalid_argument("Invalid TileOrientation string: " + str);

	}
	inline TMO::Landscape stringToLandscape(const std::string& str)
	{
		if (str == "Grass")
			return TMO::Landscape::Grassland;
		else if (str == "Forest")
			return TMO::Landscape::Forest;
		else if (str == "Hill")
			return TMO::Landscape::Hill;
		else if (str == "Mountain")
			return TMO::Landscape::Mountain;
		else if (str == "Coast")
			return TMO::Landscape::Coast;
		else if (str == "Ocean")
			return TMO::Landscape::Ocean;
		else if (str == "Error")
			return TMO::Landscape::Error;
		else
			throw std::invalid_argument("Invalid Landscape string: " + str);

	}
	using AStarMap		 = std::vector<std::vector<AStarMetaTile>>;
	using TileMap		 = std::vector<std::vector<TMO::Tile>>;
	using coordinatePath = std::vector<Coordinates>;

	struct Coordinates
	{
		int16_t x{};
		int16_t y{};

		void print() const
		{
			std::cout << "(x: " << x << " y: " << y << ")" << std::endl;
		}
		bool operator==(const Coordinates& other) const
		{ return (x == other.x && y == other.y); }
		bool operator!=(const Coordinates& other) const
		{ return (x != other.x || y != other.y); }
		// potential loss of data, but it is not a problem for this application
		Coordinates operator+(const Coordinates& other) const
		{ return Coordinates{static_cast<int16_t>(x + other.x),static_cast<int16_t>(y + other.y)}; }
		// concatenates the coordinates into a single int32_t
		std::int32_t generateHash() const
		{
			// shift coordinates to positive space to prevent hashing errors
			uint32_t shiftedX = static_cast<uint32_t>(static_cast<int32_t>(x) + 32768);
			uint32_t shiftedY = static_cast<uint32_t>(static_cast<int32_t>(y) + 32768);
			uint32_t uniqueID{ (shiftedY << 16) | shiftedX };
			return uniqueID;
		}
	};

	struct AStarMetaTile
	{
		float minimumTileCost;
		float maximumTileCost;
		AStarMetaTile(float min = 1, float max = 1) :
			minimumTileCost(min), maximumTileCost(max) {}
	};

	struct Tile
	{
		Tile() = default;
		Tile(const Coordinates coordinates, Landscape landscape)
			: coordinates(coordinates), landscape(landscape), uniqueID(coordinates.generateHash())
		{}

		const Coordinates coordinates{};
		Landscape landscape{};
		const uint32_t uniqueID{};
	};
	struct MapCreationData
	{
		int radius{};
		TileShape tileShape{};
		TileOrientation tileOrientation{};
	};
	/// OrientationKey 
	///   contains maps of tile offset Coordinates 
	///   paired with their enum Direction
	/// Strategy Design Pattern
	struct OrientationKey
	{
		using key = const std::map<Direction, TMO::Coordinates>;
		key* active;

		auto begin() const
		{
			if(active == nullptr)
				throw std::runtime_error("Error, active key is null");
			return active->begin();
		}
		auto end() const
		{
			if (active == nullptr)
				throw std::runtime_error("Error, active key is null");
			return active->end();
		}


		void setActiveKey(TMO::TileOrientation orientation)
		{
			switch (orientation)
			{
			case(TMO::TileOrientation::HexagonNS):
				active = &HexagonNSDirections;
				return;
			case(TMO::TileOrientation::HexagonEW):
				active = &HexagonEWDirections;
				return;
			case(TMO::TileOrientation::Square):
				active = &SquareDirections;
				return;
			case(TMO::TileOrientation::TriangleStandard):
				active = &TriangleStandardDirections;
				return;
			case(TMO::TileOrientation::TriangleInverted):
				active = &TriangleInvertedDirections;
				return;
			default:
				throw std::runtime_error("Error, invalid tile orientation in TMO::Compass");
			}
		}

		const key SquareDirections{
			{Direction::NorthWest, TMO::Coordinates{-1,-1}},
			{Direction::North,     TMO::Coordinates{+0,-1}},
			{Direction::NorthEast, TMO::Coordinates{+1,-1}},
			{Direction::East,      TMO::Coordinates{+1,+0}},
			{Direction::SouthEast, TMO::Coordinates{+1,+1}},
			{Direction::South,     TMO::Coordinates{+0,+1}},
			{Direction::SouthWest, TMO::Coordinates{-1,+1}},
			{Direction::West,      TMO::Coordinates{-1,+0}},
		};
		const key HexagonNSDirections{
			{Direction::NorthWest, TMO::Coordinates{-1,+0}},
			{Direction::North,     TMO::Coordinates{+0,-1}},
			{Direction::NorthEast, TMO::Coordinates{+1,-1}},
			{Direction::SouthEast, TMO::Coordinates{+1,+0}},
			{Direction::South,     TMO::Coordinates{+0,+1}},
			{Direction::SouthWest, TMO::Coordinates{-1,+1}},
		};
		const key HexagonEWDirections{
			{Direction::NorthWest, TMO::Coordinates{-1,+0}},
			{Direction::NorthEast, TMO::Coordinates{+0,-1}},
			{Direction::East,      TMO::Coordinates{+1,-1}},
			{Direction::SouthEast, TMO::Coordinates{+1,+0}},
			{Direction::SouthWest, TMO::Coordinates{+0,+1}},
			{Direction::West,      TMO::Coordinates{-1,+1}},
		};
		const key TriangleStandardDirections{
			{Direction::NorthWest,		TMO::Coordinates{-1,+0}},
			{Direction::NorthNorthWest, TMO::Coordinates{-1,-1}},
			{Direction::North,			TMO::Coordinates{+0,-1}},
			{Direction::NorthNorthEast, TMO::Coordinates{+1,-1}},
			{Direction::NorthEast,		TMO::Coordinates{+1,+0}},
			{Direction::East,			TMO::Coordinates{+2,+0}},
			{Direction::SouthEast,		TMO::Coordinates{+2,+1}},
			{Direction::SouthSouthEast, TMO::Coordinates{+1,+1}},
			{Direction::South,			TMO::Coordinates{+0,+1}},
			{Direction::SouthSouthWest, TMO::Coordinates{-1,+1}},
			{Direction::SouthWest,		TMO::Coordinates{-2,+1}},
			{Direction::West,			TMO::Coordinates{-2,+0}},
		};
		const key TriangleInvertedDirections{
			{Direction::SouthSouthEast,	TMO::Coordinates{+1,+1}},
			{Direction::South,			TMO::Coordinates{+0,+1}},
			{Direction::SouthSouthWest,	TMO::Coordinates{-1,+1}},
			{Direction::SouthWest,		TMO::Coordinates{-1,+0}},
			{Direction::West,			TMO::Coordinates{-2,+0}},
			{Direction::NorthWest,		TMO::Coordinates{+2,+0}},
			{Direction::NorthNorthWest,	TMO::Coordinates{+2,+1}},
			{Direction::North,			TMO::Coordinates{+0,-1}},
			{Direction::NorthNorthEast,	TMO::Coordinates{+1,-1}},
			{Direction::NorthEast,		TMO::Coordinates{+2,-1}},
			{Direction::East,			TMO::Coordinates{+2,+0}},
			{Direction::SouthEast,		TMO::Coordinates{+1,+0}},
		};
	};
	struct MapData
	{
		int radius{};
		TileMap map{};
		TileShape tileShape{};
		TileOrientation tileOrientation{};
		OrientationKey orientationKey{};
		// Default constructor
		MapData() = default;
		// Constructor
		MapData(
			int radius,
			TileShape tileShape,
			TileOrientation tileOrientation
		) :
			radius			{ radius },
			tileShape		{ tileShape },
			tileOrientation	{ tileOrientation }
		{
			orientationKey.setActiveKey(tileOrientation);
			map.resize(radius * 2 + 1);
			for (auto& row : map)
			{
				row.resize(radius * 2 + 1);
			}
		}

		const TMO::Tile* getTile(const TMO::Coordinates coordinates) const
		{
			if (!isValid(coordinates))
			{
				std::cout << "Invalid coordinates: " << coordinates.x << ", " << coordinates.y << std::endl;
				return nullptr;  // return no value
			}
			return &map[coordinates.x + radius][coordinates.y + radius];
		} // ^ GetTile ^

		bool isValid(const TMO::Coordinates coordinates) const
		{
			if (coordinates.x < -radius || coordinates.x > radius)
				return false;
			if (coordinates.y < -radius || coordinates.y > radius)
				return false;
			return true;
		} // ^ isValid ^

		// Checks if coordinates are within map bounds
		bool isWalkable(const TMO::Coordinates coordinates) const
		{
			// getTile checks if coordinates are valid
			const auto tile = getTile(coordinates);
			if (tile == nullptr)
			{
				return false;
			}
			TMO::Landscape landscape = tile->landscape;

			switch (landscape)
			{
			case TMO::Landscape::Coast:
				return false;
			case TMO::Landscape::Ocean:
				return false;
			case TMO::Landscape::Grassland:
				return true;
			case TMO::Landscape::Forest:
				return true;
			case TMO::Landscape::Hill:
				return true;
			case TMO::Landscape::Mountain:
				return false;
			default:
				return false;
			}
		} // ^ isWalkable ^
		// calculate movement distance depending on map tile orientation, assuming no obstacles
		int getMinimumDistance(
			const TMO::Coordinates& from,
			const TMO::Coordinates& to
		) const
		{
			int dx = abs(to.x - from.x);
			int dy = abs(to.y - from.y);
			int totalDistance{};

			switch (tileOrientation)
			{
			case TMO::TileOrientation::Square:
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
				totalDistance += (min * 14);		// diagonal movement costing x14
				totalDistance += ((max - min) * 10);// horizontal and vertical movement costing x10
				return totalDistance;
					
			case TMO::TileOrientation::HexagonNS:
				throw std::runtime_error("HexagonNS not implemented");
				return 10000;
			case TMO::TileOrientation::HexagonEW:
				throw std::runtime_error("HexagonEW not implemented");
				return 10000;
			case TMO::TileOrientation::TriangleStandard:
				throw std::runtime_error("TriangleStandard not implemented");
				return 10000;
			case TMO::TileOrientation::TriangleInverted:
				throw std::runtime_error("TriangleInverted not implemented");
				return 10000;
			default:
				throw std::runtime_error("Unknown tile orientation");
				return 10000;
				
			}
		}
	}; // struct MapData

	// ostream operators
	inline std::ostream& operator<<(std::ostream& os, const TileShape& tileShape)
	{
		switch (tileShape)
		{
		case TileShape::Hexagon:
			os << "Hexagon";
			break;
		case TileShape::Square:
			os << "Square";
			break;
		case TileShape::Triangle:
			os << "Triangle";
			break;
		default:
			os << "Unknown";
		}
		return os;
	}
	inline std::ostream& operator<<(std::ostream& os, const TileOrientation& tileOrientation)
	{
		switch (tileOrientation)
		{
		case TileOrientation::HexagonNS:
			os << "HexagonNS";
			break;
		case TileOrientation::HexagonEW:
			os << "HexagonEW";
			break;
		case TileOrientation::Square:
			os << "Square";
			break;
		case TileOrientation::TriangleStandard:
			os << "TriangleStandard";
			break;
		case TileOrientation::TriangleInverted:
			os << "TriangleInverted";
			break;
		default:
			os << "Unknown";
		}
		return os;
	}
	inline std::ostream& operator<<(std::ostream& os, const Landscape& landscape)
	{
		switch (landscape)
		{
		case Landscape::Coast:
			os << "Coast";
			break;
		case Landscape::Ocean:
			os << "Ocean";
			break;
		case Landscape::Grassland:
			os << "Grassland";
			break;
		case Landscape::Forest:
			os << "Forest";
			break;
		case Landscape::Hill:
			os << "Hill";
			break;
		case Landscape::Mountain:
			os << "Mountain";
			break;
		default:
			os << "Unknown";
		}
		return os;
	}
	inline std::ostream& operator<<(std::ostream& os, const Direction& direction)
	{
		switch (direction)
		{
		case Direction::SouthEast:
			os << "SouthEast";
			break;
		case Direction::SouthSouthEast:
			os << "SouthSouthEast";
			break;
		case Direction::South:
			os << "South";
			break;
		case Direction::SouthSouthWest:
			os << "SouthSouthWest";
			break;
		case Direction::SouthWest:
			os << "SouthWest";
			break;
		case Direction::WestSouthWest:
			os << "WestSouthWest";
			break;
		case Direction::West:
			os << "West";
			break;
		case Direction::WestNorthWest:
			os << "WestNorthWest";
			break;
		case Direction::NorthWest:
			os << "NorthWest";
			break;
		case Direction::NorthNorthWest:
			os << "NorthNorthWest";
			break;
		case Direction::North:
			os << "North";
			break;
		case Direction::NorthNorthEast:
			os << "NorthNorthEast";
			break;
		case Direction::NorthEast:
			os << "NorthEast";
			break;
		case Direction::EastNorthEast:
			os << "EastNorthEast";
			break;
		case Direction::East:
			os << "East";
			break;
		case Direction::EastSouthEast:
			os << "EastSouthEast";
			break;
		default:
			os << "Unknown";
		}
		return os;
	}
	inline std::ostream& operator<<(std::ostream& os, const TMO::Coordinates& coordinates)
	{
		os << "(x: " << coordinates.x << ", y: " << coordinates.y << ")";
		return os;
	}

} // namespace TMO