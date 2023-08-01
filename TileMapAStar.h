#pragma once

#include <queue>
#include <vector>
#include <algorithm>
#include <list>
#include <unordered_set>
#include <unordered_map>
#include <iostream>

#include "TileMapObjects.h"

class TileMapAStar
{
public:
	TMO::AStarMap generateMap(const TMO::TileMap& baseMap);
	TMO::AStarMap generateLowResolutionMap(const TMO::AStarMap& baseMap);
	void findPath(
		const TMO::Coordinates start,        // starting coordinates
		const TMO::Coordinates destination,  // destination coordinates
		const TMO::MapData& mapData,         // map data
		std::vector<TMO::Coordinates>& path);// path to be returned
private:
	struct PathNode;
	struct PathNodeHash;
	struct PathNodeEqual;

	void buildPath(std::vector<TMO::Coordinates>& path, TileMapAStar::PathNode& node);

	// pathNode used for pathfinding
	struct PathNode
	{
		PathNode* parent;
		float goneCost;
		float heuristicCost;
		TMO::Coordinates coordinates{};

		// Constructor
		PathNode(
			TMO::Coordinates coordinates,
			PathNode* parent	= nullptr,
			float goneCost		= 0,
			float heuristicCost	= 0
		) :
			coordinates(coordinates),
			parent(parent),
			goneCost(goneCost),
			heuristicCost(heuristicCost)
		{
		}
		// Copy Constructor
		PathNode(const PathNode& other) :
			parent			(other.parent),
			goneCost		(other.goneCost),
			heuristicCost	(other.heuristicCost),
			coordinates		(other.coordinates)
		{
		}
		// Assignment Operator
		PathNode& operator=(const PathNode& other)
		{
			if (this != &other)
			{
				parent			= other.parent;
				goneCost		= other.goneCost;
				heuristicCost	= other.heuristicCost;
				coordinates		= other.coordinates;
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
			return node.coordinates.generateHash();
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

	using AStarPriorityQueue = std::priority_queue<PathNode, std::vector<PathNode>, CompareNodeCost>;
	using AStarHashMap		 = std::unordered_map <int32_t, PathNode>;
	using AStarClosedSet	 = std::unordered_set <PathNode, PathNodeHash, PathNodeEqual>;   


};