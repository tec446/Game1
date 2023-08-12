#pragma once

#include "MapData.h"

namespace TileMap 
{
    class SquareMapData : public MapData {
    protected:
        TileShape m_tileShape = TileShape::Square;
    public:
        // Constructor
        SquareMapData(TileShape tileShape, int16_t radius);
        // Getters //
        const Tile* getTile(const Coordinates& coordinates) const override;
        // Setters //
        
        // Queries //
        bool isValid(const Coordinates coordinates) const override;
        // Utility //
        int calcMinMoveCost(const Coordinates& from, const Coordinates& to) const override;
        Coordinates coordinatesToIndices(const Coordinates& coordinates) const;
    }; // ^ SquareMapData ^
} // namespace TileMap
