#pragma once
#include "atom.h"

class Wall : public Atom
{
public:
	Wall(void)
	{
		opacity = Opacity::OPAQUE;
		processing = ProcessingFlag::no_process;
	}

	char render(void) override
	{
		return '#';
	}
};