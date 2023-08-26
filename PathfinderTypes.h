#pragma once

namespace TileMap::Pathfinder
{

	// Functor Declarations
	struct PathNodeHash;
	struct PathNodeEqual;
	struct CompareNodeCost;

	// Class Declarations
	class MetaTile;
	class MetaHiRes;
	class MetaLoRes;

	class PathNode;
	class PathNodeStd;
	class PathNodeHiRes;
	class PathNodeLoRes;

	/////////////////////// MetaTile ///////////////////////////////////////
	class MetaTile
	{
	protected:
		uint32_t ID{ 0 };
	}; // class MetaTile
	/////////////////////// MetaHiRes ///////////////////////////////////////
	class MetaHiRes : public MetaTile
	{
	protected:
		Coordinates coordinates{};
		std::vector<const Tile*> tiles{};
	}; // class MetaHiRes

	// Contains the coordinates of the children of a MetaHiRes on a square map
	const std::array<const Coordinates, 4> SquareMetaChildrenOffsets
	{
		Coordinates{ 0, 0 }, // South-West
			Coordinates{ 0, 1 }, // North-West
			Coordinates{ 1, 0 }, // South-East
			Coordinates{ 1, 1 }  // North-East
	}; // SquareMetaChildrenOffsets

	/////////////////////// MetaLoRes ///////////////////////////////////////
	class MetaLoRes : public MetaTile
	{
	protected:
		std::vector<const PathNodeLoRes*> children{};
	}; // class MetaLoRes


	class PathNode
	{
	public:
		float goneCost;
		float heuristicCost;
		Coordinates coordinates{};
		ReferenceTables::Direction direction{ ReferenceTables::Direction::None };

		PathNode(
			Coordinates coordinates,
			ReferenceTables::Direction direction = ReferenceTables::Direction::None,
			float goneCost = 0,
			float heuristicCost = 0
		) :
			coordinates(coordinates),
			direction(direction),
			goneCost(goneCost),
			heuristicCost(heuristicCost)
		{} // Constructor
		PathNode(const PathNode& other) :
			coordinates(other.coordinates),
			direction(other.direction),
			goneCost(other.goneCost),
			heuristicCost(other.heuristicCost)
		{} // Copy Constructor
		/// M

		bool operator==(const PathNode& other) const // Equality Operator
		{ return coordinates == other.coordinates; } // Equality Operator
		bool operator<(const PathNode& other) const  // Less Than Operator
		{ return finalCost() < other.finalCost(); }  // Less Than Operator
		bool operator>(const PathNode& other) const  // Greater Than Operator
		{ return finalCost() > other.finalCost(); }  // Greater Than Operator

		// Total cost calculated on demand to reduce redundancy
		float finalCost() const { return goneCost + heuristicCost; }
	};

	class PathNodeStd : public PathNode {};
	class PathNodeHiRes : public PathNode {};
	class PathNodeLoRes : public PathNode {};

#pragma region Functor Definitions

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

#pragma endregion
} // namespace TileMap::Pathfinder
