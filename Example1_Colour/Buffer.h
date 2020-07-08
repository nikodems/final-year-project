#ifndef _BUFFER_H
#define _BUFFER_H

#include "DXF.h"
#include <vector>

//Struct to hold a tile's path and vector data
struct Buffer
{
	XMINT3 path;
	std::vector<float> vec;

	bool operator==(const Buffer& lhs)
	{
		return	lhs.path.x == path.x &&
			lhs.path.y == path.y &&
			lhs.path.z == path.z;
	}

	Buffer(XMINT3 p, std::vector<float> v) { path = p, vec = v; }
	Buffer() {};
};

//Struct to describe a tile's position relative to the centre tile
struct TileDesc
{
	enum { NoneVert = 0, North = 1, South = -1, SouthSouth = -2, NorthNorth = 2, NorthNorthNorth = 3} vertical;
	enum  { NoneHor = 0, East = 10, West = -10 } horizontal;
};


#endif _BUFFER_H