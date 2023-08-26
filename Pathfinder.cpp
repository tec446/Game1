#include "Pathfinder.h"

namespace TileMap::Pathfinder
{
////////////////////////////////// - AStar findPath - //////////////////////////////////////////////
void AStar::findPath(
    const MapData& mapData,
    const Coordinates& start,
    const Coordinates& destination,
    Path& path
)
{
    // Validate input
    if (!mapData.hasReferenceTables())    throw std::runtime_error("Invalid references in findPath");
    if (!mapData.isWalkable(start))       throw std::runtime_error("invalid start in findPath");
    if (!mapData.isWalkable(destination)) throw std::runtime_error("invalid destination in findPath");

    OpenQueue openList;   // Unprocessed nodes, sorted by cost, lowest first
    ClosedSet closedList; // Processed nodes
    VisitedMap visited;   // Visited nodes

    resizeVisited(mapData, visited); // Resize visited map to match map size

    const auto& directionTable{ mapData.getDirectionTable() }; // All possible directions
    const auto& noveltyMap    { mapData.getNoveltyMap() };	   // All novel directions after a one tile movement

    // Create start node, process it, and add it to the closedList
    auto startNode{getNode(start, ReferenceTables::Direction::None)};
    closedList.insert(startNode);      
    processNode(mapData, startNode, destination, openList, closedList, visited, directionTable);
        
    // Run the main loop
    if (whileOpen(mapData, noveltyMap, start, destination, openList, closedList, visited, path))
    { return; }
    else // Failed to find a path
    { throw std::runtime_error("No path found!"); }
} // function findPath

////////////////////////////////// - AStar resizeVisited - /////////////////////////////////////////
// Resize visited map to match map size
inline void AStar::resizeVisited(const MapData& mapData, VisitedMap& visited)
{
    visited.resize(mapData.getTiles().size(), std::vector<bool>(mapData.getTiles()[0].size(), false));
} // function resizeVisited

////////////////////////////////// - AStar getNode - ///////////////////////////////////////////////
// Get a node for pathfinding
inline auto AStar::getNode(const Coordinates& start, const ReferenceTables::Direction direction) -> PathNode
{
    return PathNode(start, direction);
} // function getNode

////////////////////////////////// - AStar whileOpen - /////////////////////////////////////////////
// Primary pathfinding loop 
inline bool AStar::whileOpen
(
    const MapData& mapData, 
    const ReferenceTables::NoveltyMap& neighbors,
    const Coordinates& start, 
    const Coordinates& destination, 
    OpenQueue& openList, 
    ClosedSet& closedList, 
    VisitedMap& visited,
    Path& path
)
{
    while (!openList.empty())
    {
        // Find the cheapest node and pop it off the openList
        PathNode current = openList.top();
        openList.pop();

        // if we have reached the destination
        if (current.coordinates == destination)
        {
            buildPath(path, current, closedList, mapData.getOffsetMap());
            return(true);
        }
        else
        {
            closedList.insert(current);
            processNode(mapData, current, destination, openList, closedList, visited, neighbors.at(current.direction));
        }
    } // while (!openList.empty())

} // function whileOpen

////////////////////////////////// - AStar processNode - ///////////////////////////////////////////
// Adds all neighbors of the current node to the openList
inline void AStar::processNode
(
    const MapData& mapData, 
    const PathNode& node, 
    const Coordinates& destination, 
    OpenQueue& openList, 
    ClosedSet& closedList, 
    VisitedMap& visited, 
    const ReferenceTables::DirectionTable& neighbors
)
{
    // neighbor.first  = direction
    // neighbor.second = offset
    for (const auto& neighbor : neighbors)
    {
        Coordinates newCoordinates = node.coordinates + neighbor.second;

        if (mapData.isWalkable(newCoordinates))
        {
            Coordinates indices = mapData.coordinatesToIndices(newCoordinates);
            if (!visited[indices.y][indices.x]) // always stored [y][x]
            {
                // PathNode
                //   - Coordinates
                //   - Direction
                //   - Gone cost
                //   - Heuristic cost
                openList.push(
                    PathNode(
                        newCoordinates,
                        neighbor.first,
                        node.goneCost + mapData.calcMinMoveCost(node.coordinates, newCoordinates),
                        mapData.calcMinMoveCost(newCoordinates, destination)
                    ));

                visited[indices.y][indices.x] = true;
            }
        }
    }
}

////////////////////////////////// - AStar buildPath - /////////////////////////////////////////////
inline void AStar::buildPath(Path& path, const PathNode& node, const ClosedSet& closedList, const ReferenceTables::OffsetMap& offsetMap)
{
    const PathNode* currentNode = &node;
    std::deque<Coordinates> pathDeque;

    while (currentNode->direction != ReferenceTables::Direction::None)
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
}

} // namespace TileMap::Pathfinder
