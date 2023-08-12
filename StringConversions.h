#pragma once

#include <iostream>

#include "Tile.h"
#include "ReferenceTables.h"

namespace TileMap
{

	const enum TileShape stringToTileShape(const std::string& stringShape);

	inline std::ostream& operator<<(std::ostream& os, const TileShape& tileShape)
		{
			switch (tileShape)
			{
			case TileShape::Square:
				os << "Square";
				break;
			case TileShape::Hex:
				os << "Hex";
				break;
			default:
				os << "Unknown Shape!";
			}
			return os;
		} // TileShape
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
		} // Landscape
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
		} // Direction
	inline std::ostream& operator<<(std::ostream& os, const Coordinates& coordinates)
		{
			std::cout << "(" << coordinates.x << "," << coordinates.y << ")";
			return os;
		} // Coordinates

} // namespace TileMap