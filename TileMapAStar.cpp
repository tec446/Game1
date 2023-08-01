#include "TileMapAStar.h"

TMO::AStarMap TileMapAStar::generateMap(const TMO::TileMap& baseMap)
{
    TMO::AStarMap newMap{};
    // TODO: Implement
    return newMap;
}
TMO::AStarMap TileMapAStar::generateLowResolutionMap(const TMO::AStarMap& baseMap)
{
    TMO::AStarMap newMap{};
    // TODO: Implement
	return newMap;
}

// Find the optimal path from start to destination on the given map
void TileMapAStar::findPath(
    const TMO::Coordinates start,       // starting coordinates
    const TMO::Coordinates destination, // destination coordinates
    const TMO::MapData& mapData,        // map data
    std::vector<TMO::Coordinates>& path // path to be returned
)
{
    if (mapData.orientationKey.active == nullptr)
    {
        throw std::invalid_argument("invalid argument in findPath");
    }

    unsigned int pathfinderIterations{ 0 };

    AStarPriorityQueue openListQueue;   // tracks cost
    AStarHashMap       openListHashMap; // tracks parent nodes
    AStarClosedSet     closedList;	    // tracks visited nodes

    PathNode startNode{start, nullptr, 0, 0};
    openListQueue.push(startNode);
    openListHashMap.insert({ startNode.coordinates.generateHash(), startNode});

    while (!openListQueue.empty())
    {
        PathNode current = openListQueue.top();
        // only erase from queue; the hash map must keep track of the parent nodes or we create nullptrs
        openListQueue.pop();
        auto hashIterator = openListHashMap.find(current.coordinates.generateHash());
        if (hashIterator != openListHashMap.end())
        {
            current = hashIterator->second;
        }
        else
        {
			throw std::runtime_error("hash map does not contain current node!");
		}

        // if we have reached the destination
        if (current.coordinates == destination)
        {
            std::cout << "\nPathfind: (" << start.x << "," << start.y << ")->(" << destination.x << "," << destination.y << ") - Success reached after : " << pathfinderIterations << " iterations";
            buildPath(path, current);
            return;
        }
        // else add the current node to the closed list
        closedList.insert(current);

        pathfinderIterations += 1;

        // Process all adjacent nodes
        for (const auto& entry : *(mapData.orientationKey.active))
        {
            const TMO::Coordinates offset = entry.second;
            TMO::Coordinates newCoordinates{current.coordinates.x + offset.x, current.coordinates.y + offset.y};
            
            if (mapData.isWalkable(newCoordinates))
            {
                std::cout << "\nvalid tile: (" << newCoordinates.x << "," << newCoordinates.y << " - " << mapData.getTile(newCoordinates)->landscape << " )";
                PathNode neighbor(newCoordinates, &current, 0, 0);

                // if neighbor is in closed list
                if (closedList.find(neighbor) != closedList.end())
                    continue;

                // Calculate cost to reach this neighbor from start
                int tentativeGone = current.goneCost + mapData.getMinimumDistance(current.coordinates, neighbor.coordinates);

                // if neighbor is not in open list, checked using hash values
                auto nodeInList = openListHashMap.find(neighbor.coordinates.generateHash());
                if (nodeInList == openListHashMap.end())
                {
                    // create a new node and add it to the open list
                    neighbor.goneCost      = tentativeGone;
                    neighbor.heuristicCost = mapData.getMinimumDistance(neighbor.coordinates, destination);

                    auto inserted = openListHashMap.insert({ neighbor.coordinates.generateHash(), neighbor });

                    inserted.first->second.parent = &(hashIterator->second);

                    openListQueue.push(neighbor);
                }
                else if (tentativeGone < (nodeInList->second.goneCost))
                {
					// update the hash node to use the new path
                    nodeInList->second.parent   = &(hashIterator->second);
                    nodeInList->second.goneCost = tentativeGone;
                }
                else
                {
                    continue;
                }
            } // if valid and walkable
        } // for adjacent nodes
    } // while open list not empty
    std::cout << "\n\tNo path possible!";
}
// constructs a path of coordinates from a path of pathNodes then reverses it
void TileMapAStar::buildPath(std::vector<TMO::Coordinates>& path, TileMapAStar::PathNode& node)
{
    while(node.parent != nullptr)
    {
    path.push_back(node.coordinates);
    node = *node.parent;
    }

	std::reverse(path.begin(), path.end());
    return;
}


