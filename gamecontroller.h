#pragma once
#include <vector>
#include "map.h"
#include <cassert>


class Atom;
class Mob;
class ClientMob;


class GameController
{
public:
	GameController(void) = default;

	std::vector<Atom*> atoms;
	std::vector<Mob*> mobs;
	
	std::vector<Atom*> processing;

	Map map;

	void updateProcessingFlag(Atom* atom);

	// TODO: move this out.
	template<typename T>
	T* createAtom(size_t x, size_t y)
	{
		assert(map.testCoordinates(x, y));
		T* created = dynamic_cast<T*>(map.access(x, y) = new T);

		assert(created);

		atoms.push_back(created);
		if (Mob* mob = dynamic_cast<Mob*>(created); mob)
			mobs.push_back(mob);

		updateProcessingFlag(created);
		created->pi = map.dump(x, y);
		return created;
	}


	bool initialized = false;

	void handleMovement(Atom* atom, PositionInfo newPosition);

	bool canMove(size_t x, size_t y, size_t nx, size_t ny);

	void tick(void);

	unsigned long long curtick = 0;
};

inline GameController* gc = nullptr;