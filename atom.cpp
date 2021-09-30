#include "atom.h"
#include "client.h"
#include "utils.h"
#include "gamecontroller.h"

std::string Atom::getName(void) const
{
	return std::string();
}

std::string Atom::getDescription(void) const
{
	return std::string();
}

void Atom::examine(ClientMob& client)
{
	std::string result = getName() + "\n" + getDescription();
	client.sendMessage(result);
}

void Atom::process(void)
{
}

void Atom::updateOpacity(Opacity newOpacity)
{
	opacity = newOpacity;
}

void Atom::updateProcessing(ProcessingFlag newProcessing)
{
	GC_ASSERT();

	if (processing == newProcessing)
		return;
	processing = newProcessing;

	gc->updateProcessingFlag(this);
}

void Atom::move(PositionInfo newPosition)
{
	GC_ASSERT();

	gc->handleMovement(this, newPosition);
}

bool Atom::onMoveAttempt(Mob& mob)
{
	return opacity == Opacity::TRANSPARENT;
}

char Atom::render(void)
{
	return '?';
}
