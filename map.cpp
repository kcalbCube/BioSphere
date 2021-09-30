#include "map.h"
#include "atom.h"
#include <cassert>

Map::Map(size_t sx, size_t sy)
	: sizeX{ sx }, sizeY{ sy } {}

Atom*& Map::access(size_t x, size_t y)
{
	return map[y][x];
}

bool Map::testCoordinates(size_t x, size_t y)
{
	return (x >= 0 && x < sizeX) && (y >= 0 && y < sizeY);
}

std::vector<Atom*> Map::locateInArea(Area& area)
{
	std::vector<Atom*> toreturn;
	toreturn.reserve(area.size());
	for(Vector2 xy : area)
		if(Atom* atom = access(xy.x, xy.y); atom)
			toreturn.push_back(atom);

	return toreturn;
}

Area& Map::locateArea(const PositionInfo& pi)
{
	if (Area* area = pi.area; area)
		return *area;
	return *xy2area[{pi.x, pi.y}];
}

PositionInfo Map::dump(size_t x, size_t y)
{
	return
	{
		x,
		y,
		& locateArea({x, y})
	};
}
PositionInfo Map::dump(Atom* atom)
{
	auto loc = (PositionInfo)*atom;
	return dump(loc.x, loc.y);
}

void Map::createMapArrays(void)
{
	map = new Atom** [sizeY];
	for (size_t i = 0; i < sizeY; ++i)
	{
		map[i] = new Atom * [sizeX];
		for (size_t j = 0; j < sizeX; ++j)
			map[i][j] = nullptr;
	}
}

void Map::generateAreas(void)
{

}

void Map::move(size_t x, size_t y, size_t nx, size_t ny)
{
	std::swap(access(x, y), access(nx, ny));
	auto t1 = access(nx, ny);
	auto t2 = access(x, y);
	if(t1)
		t1->pi = dump(nx, ny);
	if(t2)
		t2->pi = dump(x, y);
}
