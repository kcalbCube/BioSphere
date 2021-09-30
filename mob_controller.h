#pragma once
#include <string>

class Mob;
class MobController
{
public:
	Mob* owner = nullptr;

	virtual ~MobController(void) = default;
	MobController(Mob& mob) : owner{ &mob } {}
	virtual void process(void) {}
};

class EnemyController
{

};