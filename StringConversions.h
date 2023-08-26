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
			case TileShape::Hexagon:
				os << "Hexagon";
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
	inline std::ostream& operator<<(std::ostream& os, const ReferenceTables::Direction& direction)
		{
			switch (direction)
			{
			case ReferenceTables::Direction::SouthEast:
				os << "SouthEast";
				break;
			case ReferenceTables::Direction::SouthSouthEast:
				os << "SouthSouthEast";
				break;
			case ReferenceTables::Direction::South:
				os << "South";
				break;
			case ReferenceTables::Direction::SouthSouthWest:
				os << "SouthSouthWest";
				break;
			case ReferenceTables::Direction::SouthWest:
				os << "SouthWest";
				break;
			case ReferenceTables::Direction::WestSouthWest:
				os << "WestSouthWest";
				break;
			case ReferenceTables::Direction::West:
				os << "West";
				break;
			case ReferenceTables::Direction::WestNorthWest:
				os << "WestNorthWest";
				break;
			case ReferenceTables::Direction::NorthWest:
				os << "NorthWest";
				break;
			case ReferenceTables::Direction::NorthNorthWest:
				os << "NorthNorthWest";
				break;
			case ReferenceTables::Direction::North:
				os << "North";
				break;
			case ReferenceTables::Direction::NorthNorthEast:
				os << "NorthNorthEast";
				break;
			case ReferenceTables::Direction::NorthEast:
				os << "NorthEast";
				break;
			case ReferenceTables::Direction::EastNorthEast:
				os << "EastNorthEast";
				break;
			case ReferenceTables::Direction::East:
				os << "East";
				break;
			case ReferenceTables::Direction::EastSouthEast:
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