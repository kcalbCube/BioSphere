#pragma once
#include "utils.h"
#include <vector>
#include <deque>
#include <map>
#include "atom.h"
#include <list>

class Map
{
public:
	std::list<Area> areas;
	Atom*** map   = nullptr;

	std::unordered_map<Vector2, Area*> xy2area;

	size_t sizeX = 0, sizeY = 0;
	Map(void) = default;
	Map(size_t sx, size_t sy);

	/*
	*	returns: Atom pointer or nullptr.
	*/
	Atom*& access(size_t x, size_t y);

	// O(N).
	std::vector<Atom*> locateInArea(Area& area);

	// O(1).
	Area& locateArea(const PositionInfo& atom);

	PositionInfo dump(size_t x, size_t y);
	PositionInfo dump(Atom* atom);

	void createMapArrays(void);
	void generateAreas(void);

	// swap [x, y] and [nx, ny], with PI update.
	void move(size_t x, size_t y, size_t nx, size_t ny);



	bool testCoordinates(size_t x, size_t y);
	
};

