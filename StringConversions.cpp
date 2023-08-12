#include "StringConversions.h"

namespace TileMap
{
	const enum TileShape stringToTileShape(const std::string& stringShape)
	{
		if (stringShape == "Square") { return(TileShape::Square); }
		if (stringShape == "Hex") { return(TileShape::Hex); }
		else
		{
		
			throw std::runtime_error("Unknown tile shape!");
			return(TileShape::TileShape_None);
		}
	}
} // namespace TileMap