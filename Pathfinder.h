#pragma once

#include <queue>
#include <vector>
#include <algorithm>
#include <list>
#include <unordered_set>
#include <unordered_map>
#include <iostream>
#include <stdexcept>
#include <deque>

#include "Tile.h"
#include "MapData.h"
#include "ReferenceTables.h"
#include "PathfinderTypes.h"

namespace TileMap::Pathfinder
{
	// Aliases used in the A* algorithm
	// Swapped out based on search type
	namespace aliases
	{
		//using OpenQueue		 = std::priority_queue<PathNodeStd, std::vector<PathNodeStd>, std::greater<PathNodeStd>>;
		using OpenQueue		 = std::priority_queue<PathNode, std::vector<PathNode>, std::greater<PathNode>>;
		using ClosedSet		 = std::unordered_set<PathNode, PathNodeHash, PathNodeEqual>;
		using VisitedMap2D	 = std::vector<std::vector<bool>>;
		using VisitedMap1D	 = std::vector<bool>;
		using Path			 = std::vector<Coordinates>;
		using OpenQueueHiRes = std::priority_queue<PathNodeHiRes, std::vector<PathNodeHiRes>, std::greater<PathNodeHiRes>>;
		using OpenQueueLoRes = std::priority_queue<PathNodeLoRes, std::vector<MetaLoRes>, std::greater<MetaLoRes>>;
	} // namespace aliases
	/////////////////////// A* Search ///////////////////////////////////////
	class AStar
	{
	private:
		using OpenQueue  = aliases::OpenQueue;
		using ClosedSet  = aliases::ClosedSet;
		using VisitedMap = aliases::VisitedMap2D;
		using Path		 = aliases::Path;
	protected:
		inline static void resizeVisited(const MapData& mapData, VisitedMap& visited);
		inline static auto getNode(const Coordinates& start, ReferenceTables::Direction direction) -> PathNode;
		// Finds all neighbors of a node and adds them to the open list
		inline static void processNode
		(
			const MapData&	   mapData,
			const PathNode&	   node,
			const Coordinates& destination,
			OpenQueue&		   openList,
			ClosedSet&		   closedList,
			VisitedMap&		   visited,
			const ReferenceTables::DirectionTable& neighbors
		); // function processNode
		// Main loop of the A* algorithm
		inline static bool whileOpen
		(
			const MapData& mapData,
			const ReferenceTables::NoveltyMap& neighbors,
			const Coordinates& start,
			const Coordinates& destination,
			OpenQueue& openList,
			ClosedSet& closedList,
			VisitedMap& visited,
			Path& path
		); // function whileOpen
		// Builds the path from the closed list, after the destination is reached
		inline static void buildPath
		(
			Path& path, 
			const PathNode& node, 
			const ClosedSet& closedList, 
			const ReferenceTables::OffsetMap& offsetMap
		); // function buildPath

	public:
		static void findPath
		(
			const MapData&			  mapData,          
			const Coordinates&		  start,         
			const Coordinates&		  destination,   
			Path& path
		); // findPath

	}; // class AStar
	/////////////////////// Jump Point Search ///////////////////////////////
	class JumpPointSearch : public AStar
	{
	private:
		using OpenQueue  = aliases::OpenQueue;
		using ClosedSet  = aliases::ClosedSet;
		using VisitedMap = aliases::VisitedMap2D;
		using Path		 = aliases::Path;
	protected:

	public:

	}; // class JumpPointSearch
	/////////////////////// High Resolution Search //////////////////////////
	class AStarHiRes : public AStar
	{
	private:
		using OpenQueue  = aliases::OpenQueueHiRes;
		using ClosedSet  = aliases::ClosedSet;
		using VisitedMap = aliases::VisitedMap1D;
		using Path		 = aliases::Path;

	protected:

	}; // class AStarHiRes
	/////////////////////// Low Resolution Search ///////////////////////////
	class AStarLoRes : public AStar
	{
	private:
		using OpenQueue  = aliases::OpenQueueLoRes;
		using ClosedSet  = aliases::ClosedSet;
		using VisitedMap = aliases::VisitedMap2D;
		using Path		 = aliases::Path;
	protected:
	}; // class AStarLoRes
}; // TileMap::Pathfinder