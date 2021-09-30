#include "mob.h"

void Mob::process(void)
{
	if (mc)
		mc->process();
}
