#pragma once

#include <stdexcept>
#include <cmath>
#include <cstdint>
#include <vector>
#include <map>

namespace TileMap 
{
	struct Tile; 
	struct Coordinates;

	enum Landscape
	{
		Coast,
		Ocean,
		Grassland,
		Forest,
		Hill,
		Mountain,
		Landscape_None,
	};
	enum TileShape
	{
		Square,
		Hexagon,
		TileShape_None,
	};

	struct Coordinates
	{
		int16_t x{};
		int16_t y{};

		Coordinates() = default;
		Coordinates(int16_t x, int16_t y) : x(x), y(y) {}
#pragma region operatorOverrides
		// operator overrides
		// operator + is used to modify Coordinates by an Offset
		Coordinates operator+(const Coordinates& other) const
		{
			return(Coordinates(x + other.x, y + other.y));
		} // ^ operator + ^
		bool operator==(const Coordinates& other) const
		{
			return (x == other.x && y == other.y);
		} // ^ operator == ^
		bool operator!=(const Coordinates& other) const
		{
			return (x != other.x || y != other.y);
		} // ^ operator != ^
		bool operator>(const Coordinates& other) const
		{
			return std::tie(x, y) > std::tie(other.x, other.y);
		} // ^ operator > ^
		bool operator<(const Coordinates& other) const
		{
			return std::tie(x, y) < std::tie(other.x, other.y);
		} // ^ operator < ^
#pragma endregion
	}; // Coordinates

	// HashCoordinates - concatenates the coordinates into a single int32_t
	struct HashCoordinates 
	{
		std::int32_t operator()(const Coordinates& coordinates) const
		{
			// shift coordinates to positive space to prevent hashing errors
			uint32_t shiftedX = static_cast<uint32_t>(static_cast<int32_t>(coordinates.x) + 32768);
			uint32_t shiftedY = static_cast<uint32_t>(static_cast<int32_t>(coordinates.y) + 32768);
			uint32_t uniqueID{ (shiftedY << 16) | shiftedX };
			return uniqueID;
		}
	}; // HashCoordinates

	struct Tile
	{
		const Coordinates coordinates{};
		const uint32_t uniqueID{};
		Landscape landscape{};
		// Constructors
		Tile() = default;
		Tile(const Coordinates coordinates, Landscape landscape)
			: coordinates(coordinates), uniqueID(HashCoordinates()(coordinates)), landscape(landscape) {}
		Tile& operator=(const Tile& other) {
			if (this != &other) {
				landscape = other.landscape;
			}
			return *this;
		}

	};
}