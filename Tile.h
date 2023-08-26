#pragma once

#include <stdexcept>
#include <cmath>
#include <cstdint>
#include <vector>
#include <map>
#include <array>

namespace TileMap 
{
	class Tile; 
	struct Coordinates;
	struct SquareMetaTile;

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
<<<<<<< Updated upstream
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
=======
		Coordinates operator+(const Coordinates& other) const	//  + operator +
		{ return(Coordinates(x + other.x, y + other.y)); }		//  + operator +
		Coordinates operator-(const Coordinates& other) const	//  - operator -
		{ return(Coordinates(x - other.x, y - other.y)); }		//  - operator -
		bool operator==(const Coordinates& other) const			// == operator ==
		{ return (x == other.x && y == other.y); }				// == operator ==
		bool operator!=(const Coordinates& other) const			// != operator !=
		{ return (x != other.x || y != other.y); }				// != operator !=
		bool operator>(const Coordinates& other) const			//  > operator >
		{ return std::tie(x, y) > std::tie(other.x, other.y); }	//  > operator >
		bool operator<(const Coordinates& other) const			//  < operator <
		{ return std::tie(x, y) < std::tie(other.x, other.y); }	//  < operator <
>>>>>>> Stashed changes
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

	class Tile
	{
	public:
		const Coordinates coordinates{}; // const to prevent modification, coordinates are unique		     and should never change
		const uint32_t uniqueID{};		 // const to prevent modification, uniqueID is a hash of coordinates and should never change
		Landscape landscape{};
		// Constructors
		Tile() = default;
		Tile(const Coordinates coordinates, Landscape landscape)
			: coordinates(coordinates), uniqueID(HashCoordinates()(coordinates)), landscape(landscape) {}
		// Operator Overrides
		Tile& operator=(const Tile& other) {
			if (this != &other) {
				landscape = other.landscape;
			}
			return *this;
		} // = operator =
	}; // Tile

	struct SquareMetaTile
	{
		Coordinates coordinates{};
		uint32_t ID{};
		int16_t internalMinCost{ 10 }; //	one cardinal move
		int16_t internalMaxCost{ 28 }; // two diagonal moves
		int16_t goneCost{};
		int16_t heuristicCost{};
		int16_t totalCost{};
		// maybe south-to-north cost?
		// east-to-west cost?
		// and so on...
		// or something

		const Tile* northWest{ nullptr };
		const Tile* northEast{ nullptr };
		const Tile* southWest{ nullptr };
		const Tile* southEast{ nullptr };

		std::array<SquareMetaTile*, 8> neighbors{};

		// Constructors
		SquareMetaTile() = default;

		///
		///    NW  N  NE
		///          
		///    W   X   E
		/// 
		///    SW  S  SE
		/// 
		/// NorthWest if(NorthWest != nullptr)
		/// North     if(NorthWest != nullptr || NorthEast != nullptr)
		/// NorthEast if(NorthEast != nullptr)
		/// East      if(NorthEast != nullptr || SouthEast != nullptr)
		/// SouthEast if(SouthEast != nullptr)
		/// South     if(SouthEast != nullptr || SouthWest != nullptr)
		/// SouthWest if(SouthWest != nullptr)
		/// West      if(SouthWest != nullptr || NorthWest != nullptr)
		/// 
		/// sortedCosts = sort(NorthWest, NorthEast, SouthEast, SouthWest)
		/// internalMinCost = 10 one cardinal move
		/// internalMaxCost = 28 two diagonal moves
		/// 

	};

}