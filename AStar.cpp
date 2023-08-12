#include "AStar.h"
#include <deque>

namespace TileMap
{
    /////////////////////////////////////// - findPath - ////////////////////////////////////////////
    // Find the optimal path from start to destination on the given map
    void AStar::findPath(
        const Coordinates start,       // starting coordinates
        const Coordinates destination, // destination coordinates
        const MapData& mapData,        // map data
        std::vector<Coordinates>& path // path to be returned
    )
    {
        if (!mapData.hasReferenceTables())    throw std::runtime_error("Invalid references in findPath");
        if (!mapData.isWalkable(start))       throw std::runtime_error("invalid start in findPath");
        if (!mapData.isWalkable(destination)) throw std::runtime_error("invalid destination in findPath");

        AStarPriorityQueue openList;   // Tracks node cost
        AStarClosedSet     closedList; // Contains processed nodes
        AStarMap		   visited;    // Tracks visited nodes

        Map map{ mapData.getMap() };
        DirectionTable directionTable{ mapData.getDirectionTable() };
        NoveltyMap     noveltyMap    { mapData.getNoveltyMap()     };
        OffsetMap	   offsetMap     { mapData.getOffsetMap()      };

        visited.resize(map.size());
        for (int row = 0; row < visited.size(); ++row) { visited[row].resize(map[row].size()); }

        PathNode startNode{ start, Direction::Direction_None};

        // Lambda for processing a node
        auto processNode = [&](PathNode& node, const std::vector<std::pair<Direction, Coordinates>>& neighbors)
        {
            for (const auto& entry : neighbors)
            {
                const Direction direction = entry.first;
                const Coordinates offset = entry.second;
                Coordinates newCoordinates = node.coordinates + offset;

                if (mapData.isWalkable(newCoordinates) )
                {
                    Coordinates indices = mapData.coordinatesToIndices(newCoordinates);
                    if (!visited[indices.y][indices.x]) // always stored [y][x]
                    {
                        float newGone = node.goneCost + mapData.calcMinMoveCost(node.coordinates, newCoordinates);
                            float tentativeHeuristic = mapData.calcMinMoveCost(newCoordinates, destination);

                            PathNode neighbor(
                                newCoordinates,
                                direction,
                                newGone,
                                tentativeHeuristic
                            );

                        openList.push(std::move(neighbor));
                        visited[indices.y][indices.x] = true;
                    }
                }
            }
        };
        // Lambda for building the path
        auto buildPath = [&closedList, &offsetMap](std::vector<Coordinates>& path, PathNode& node)
        {
            const PathNode* currentNode = &node;
            std::deque<Coordinates> pathDeque;

            while (currentNode->direction != Direction::Direction_None)
            {
                pathDeque.push_front(currentNode->coordinates);

                auto it = std::find_if(closedList.begin(), closedList.end(),
                    [&currentNode, &offsetMap](const PathNode& node)
                    { return node.coordinates == currentNode->coordinates - offsetMap.at(currentNode->direction); });

                if (it == closedList.end())
                {
                    throw std::runtime_error("Parent node not found in closed list!");
                }

                currentNode = &(*it); // Update the current node to its parent for the next iteration
            }

            path.assign(pathDeque.begin(), pathDeque.end());
        };

        // Process start node independently, using all directions
        Coordinates startIndices = mapData.coordinatesToIndices(start);
        visited[startIndices.y][startIndices.x] = true;
        closedList.insert(startNode);
        processNode(startNode, directionTable );

        // Main loop
        while (!openList.empty())
        {
            // Find the cheapest node
            PathNode current = openList.top();
            // Pop it off the list
            openList.pop();

            // if we have reached the destination
            if (current.coordinates == destination)
            {
                buildPath(path, current);
                return;
            }
            else
            {
                closedList.insert(current);
                processNode(current, noveltyMap.at(current.direction));
            }
        }

        // If we reach this point, there is no path
        throw std::runtime_error("\n\tNo path possible!");
    }
} // namespace TileMap
