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

	using AStarPriorityQueue = std::priority_queue<PathNode, std::vector<PathNode>, std::greater<PathNode>>;
	using AStarClosedSet     = std::unordered_set<PathNode, PathNodeHash, PathNodeEqual>;
	using AStarMap		     = std::vector<std::vector<bool>>;

	// pathNode used for pathfinding
	struct PathNode
	{
		float goneCost;
		float heuristicCost;
		Coordinates coordinates{};
		Direction direction{Direction::Direction_None};

		// Constructor
		PathNode(
			Coordinates coordinates,
			Direction direction		 = Direction::Direction_None,
			float goneCost			 = 0,
			float heuristicCost		 = 0
		) :
			coordinates  (coordinates),
			direction    (direction),
			goneCost     (goneCost),
			heuristicCost(heuristicCost)
		{
		}
		// Equality Operator
		bool operator==(const PathNode& other) const
		{ return coordinates == other.coordinates; }
		// Less Than Operator
		bool operator<(const PathNode& other) const
		{ return finalCost() < other.finalCost(); }
		// Greater Than Operator
		bool operator>(const PathNode& other) const
		{ return finalCost() > other.finalCost(); }
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