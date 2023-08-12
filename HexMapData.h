#pragma once

#include "MapData.h"

namespace TileMap
{
    class HexMapData : public MapData {
    protected:
		TileShape m_tileShape = TileShape::Hex;
    public:
        // Constructor
        HexMapData(TileShape tileShape, int16_t radius);
        // Getters //
        const Tile* getTile(const Coordinates& coordinates) const override;
        // Setters //
        
        // Queries //
        bool isValid(const Coordinates coordinates) const override;
        // Utility //
        int calcMinMoveCost(const Coordinates& from, const Coordinates& to) const override;
        Coordinates coordinatesToIndices(const Coordinates& coordinates) const;
    private:
        bool areValidIndices(const Coordinates& indices) const;
    }; // ^ HexMapData ^
} // namespace TileMap