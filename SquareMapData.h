#pragma once

#include "MapData.h"

namespace TileMap 
{
    // Stored within SquareMapData lowResMaps for pathfinding
    class SquareMapDataAStar;
    class SquareMapData;

    // Stores MapData for a square grid
    class SquareMapData : public MapData {
    protected:
        TileShape m_tileShape = TileShape::Square;
    public:

        SquareMapData(TileShape tileShape, int16_t radius) : MapData(tileShape, radius) {};

        const Tile* getTile(const Coordinates& coordinates) const override;
        const std::shared_ptr<const MapData> getLowResMap() const;

        bool isValid(const Coordinates& coordinates) const override;

        int calcMinMoveCost(const Coordinates& from, const Coordinates& to) const override;
        Coordinates coordinatesToIndices(const Coordinates& coordinates) const override;
        void generateLowResMap() override;

    private:
        // Used for pathfinding
        std::shared_ptr<SquareMapDataAStar> m_lowResMap{};
   }; // ^ SquareMapData ^

    // Stored within SquareMapData lowResMaps for pathfinding
    class SquareMapDataAStar : public SquareMapData 
    {
    public:
        void setMap(const std::vector<std::vector<SquareMetaTile>>& map);

        SquareMapDataAStar(TileShape tileShape, int16_t radius) : SquareMapData(tileShape, radius) {}
    protected:
        std::vector<std::vector<SquareMetaTile>> m_tiles{};
    };
} // namespace TileMap