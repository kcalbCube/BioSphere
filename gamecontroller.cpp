#include "gamecontroller.h"
#include <cassert>
#include "atom.h"
#include <ranges>
#include <algorithm>
#include <type_traits>
#include "mob.h"


void GameController::updateProcessingFlag(Atom* atom)
{
	assert(atom);
	switch (atom->processing)
	{
	case ProcessingFlag::no_process:
		if (std::binary_search(processing.begin(), processing.end(), atom))
			processing.erase(std::ranges::find(processing, atom));
		break;
	case ProcessingFlag::process_each_second_tick:
	case ProcessingFlag::process_each_tick:
		if (!std::binary_search(processing.begin(), processing.end(), atom))
			processing.push_back(atom);
		break;
	}
}

bool GameController::canMove(size_t x, size_t y, size_t nx, size_t ny)
{
	Atom* atom = map.access(nx, ny);
	if (atom == nullptr)
		return true;
	return atom->onMoveAttempt(*dynamic_cast<Mob*>(map.access(x, y)));
}

void GameController::handleMovement(Atom* atom, PositionInfo positionInfo)
{
	if (!canMove(atom->pi.x, atom->pi.y, positionInfo.x, positionInfo.y))
		return;

	map.move(atom->pi.x, atom->pi.y, positionInfo.x, positionInfo.y);
}

void GameController::tick(void)
{
	for (Atom*& atom : processing)
	{
		if (atom->processing == ProcessingFlag::process_each_second_tick && (curtick % 2))
			continue;
		atom->process();
	}
	++curtick;
}