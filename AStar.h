#pragma once

#include <queue>
#include <vector>
#include <algorithm>
#include <list>
#include <unordered_set>
#include <unordered_map>
#include <iostream>
#include <stdexcept>

#include "Tile.h"
#include "MapData.h"
#include "ReferenceTables.h"
//temporary
#include "StringConversions.h"
//temporary



namespace TileMap 
{

class AStar
{
public:
	static void findPath(
		const Coordinates start,         // starting coordinates
		const Coordinates destination,   // destination coordinates
		const MapData& mapData,          // map data
		std::vector<Coordinates>& path); // path to be returned
private:
	struct PathNode;
	struct PathNodeHash;
	struct PathNodeEqual;

	static void buildPath(std::vector<Coordinates>& path, AStar::PathNode& node);

	// pathNode used for pathfinding
	struct PathNode
	{
		std::unique_ptr<PathNode> parent;
		float goneCost;
		float heuristicCost;
		Coordinates coordinates{};
		Direction direction{Direction::Direction_None};

		// Constructor
		PathNode(
			Coordinates coordinates,
			Direction direction		 = Direction::Direction_None,
			PathNode* parent		 = nullptr,
			float goneCost			 = 0,
			float heuristicCost		 = 0
		) :
			coordinates  (coordinates),
			direction    (direction),
			parent       (parent ? std::make_unique<PathNode>(*parent) : nullptr),
			goneCost     (goneCost),
			heuristicCost(heuristicCost)
		{
		}
		// Deep Copy Constructor
		PathNode(const PathNode& other) :
			direction    (other.direction),
			goneCost     (other.goneCost),
			heuristicCost(other.heuristicCost),
			coordinates  (other.coordinates)
		{
			if (other.parent) { parent = std::make_unique<PathNode>(*other.parent); }
			else			  { parent = nullptr; }
		}
		// Deep Assignment Operator
		PathNode& operator=(const PathNode& other)
		{
			if (this != &other)
			{
				direction     = other.direction;
				goneCost      = other.goneCost;
				heuristicCost = other.heuristicCost;
				coordinates   = other.coordinates;
				
				if (other.parent) { parent = std::make_unique<PathNode>(*other.parent); }
				else			  { parent = nullptr; }
			}
			return *this;
		}
		// Equality Operator
		bool operator==(const PathNode& other) const
		{
			return coordinates == other.coordinates;
		}
		// Total cost calculated on demand to reduce redundancy
		float finalCost() const
		{
			return goneCost + heuristicCost;
		}
	};
	struct PathNodeHash
	{
		std::int32_t operator()(const PathNode& node) const
		{
			return (HashCoordinates()(node.coordinates));
		}
	};
	struct PathNodeEqual
	{
		bool operator()(const PathNode& a, const PathNode& b) const
		{
			return a.coordinates == b.coordinates;
		}
	};
	struct CompareNodeCost
	{
		bool operator()(const PathNode& a, const PathNode& b) const
		{
			return a.finalCost() > b.finalCost();
		}
	};




};

} // TileMap