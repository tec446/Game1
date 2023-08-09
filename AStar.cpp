#include "AStar.h"

namespace TileMap
{
#pragma region findPath
    /////////////////////////////////////// - findPath - ////////////////////////////////////////////
    // Find the optimal path from start to destination on the given map
    void AStar::findPath(
        const Coordinates start,       // starting coordinates
        const Coordinates destination, // destination coordinates
        const MapData& mapData,        // map data
        std::vector<Coordinates>& path // path to be returned
    )
    {
        using AStarPriorityQueue = std::priority_queue<PathNode, std::vector<PathNode>, CompareNodeCost>;
        using AStarClosedSet     = std::unordered_set <PathNode, PathNodeHash, PathNodeEqual>;

        if (!mapData.validReferences() )       throw std::runtime_error("Invalid references in findPath" ); 
        if (!mapData.isWalkable(start) )       throw std::runtime_error("invalid start in findPath");
        if (!mapData.isWalkable(destination) ) throw std::runtime_error("invalid destination in findPath");

        AStarPriorityQueue openList;   // tracks cost
        AStarClosedSet     closedList; // tracks visited nodes

        PathNode startNode{ start };
        openList.push(startNode);

        while (!openList.empty())
        {
            PathNode current = openList.top();
            openList.pop();

            // if we have reached the destination
            if (current.coordinates == destination)
            {
                buildPath(path, current);
                return;
            }
            // else add the current node to the closed list
            closedList.insert(current);

            std::vector<std::pair<Direction, Coordinates>> const* neighbors{ nullptr };
            // if we are at the start, use all neighbors, else use novel neighbors
            if (current.parent == nullptr) { neighbors = &(*mapData.directionTable                  ); }
            else                           { neighbors = &(*mapData.noveltyMap).at(current.direction); }

            // Process new neighbors
            for (const auto& entry : *neighbors)
            {
                const Direction direction  = entry.first;
                const Coordinates offset   = entry.second;
                Coordinates newCoordinates = current.coordinates + offset;

                if (mapData.isWalkable(newCoordinates))
                {
                    // Calculate costs to reach this neighbor from start
                    float tentativeGone      = current.goneCost + mapData.getMinimumMoveCost(current.coordinates, newCoordinates);
                    float tentativeHeuristic = mapData.getMinimumMoveCost(newCoordinates, destination);

                    PathNode neighbor(
                        newCoordinates,
                        direction,
                        &current,
                        tentativeGone,
                        tentativeHeuristic
                    );

                    if (closedList.find(neighbor) != closedList.end()) continue;
                    else openList.push(neighbor);
                } // if (walkable)
            } // for (neighbor : neighbors)
        } // while (openList != empty)
        throw std::runtime_error("\n\tNo path possible!");
    } // findPath
    /////////////////////////////////////// - findPath - ////////////////////////////////////////////
#pragma endregion
    // constructs a path of coordinates from a path of pathNodes then reverses it
    void AStar::buildPath(std::vector<Coordinates>& path, AStar::PathNode& node)
    {
        while (node.parent != nullptr)
        {
            path.push_back(node.coordinates);
            node = *node.parent;
        }
        std::reverse(path.begin(), path.end());
        return;
    } // ^ buildPath ^
} // namespace TileMap