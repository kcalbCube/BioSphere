#pragma once
#include "mob.h"

struct Stats
{
	uint16_t health = 0;
	uint16_t reflexion = 0;
	uint8_t strength = 0;
	uint8_t dexterity = 0;
	uint8_t intelligence = 0;
};
// mob with client linked.
class ClientMob : public Mob
{
public:
	Stats stats;
	void sendMessage(const std::string& message);
};

