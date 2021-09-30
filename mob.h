#pragma once
#include "atom.h"
#include "mob_controller.h"

class Mob : public Atom
{
public:
	MobController* mc = nullptr;

	Mob(void)
	{
		opacity = Opacity::OPAQUE;
	}

	void process(void) override;
};

