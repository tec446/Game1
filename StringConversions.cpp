#include "StringConversions.h"

namespace TileMap
{
	const enum TileShape stringToTileShape(const std::string& stringShape)
	{
		if (stringShape == "Square") { return(TileShape::Square); }
		if (stringShape == "HexagonNS") { return(TileShape::HexagonNS); }
		if (stringShape == "HexagonEW") { return(TileShape::HexagonEW); }
		if (stringShape == "TriangleStandard") { return(TileShape::TriangleStandard); }
		if (stringShape == "TriangleInverted") { return(TileShape::TriangleInverted); }
		else return(TileShape::TileShape_None);
	}
} // namespace TileMap