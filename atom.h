#pragma once
#include <string>
#include <vector>
#include <tchar.h>
#include "utils.h"


class Mob;
class ClientMob;

enum class ProcessingFlag
{
	no_process
	, process_each_tick
	, process_each_second_tick
};

enum class Opacity
{
	TRANSPARENT
	, OPAQUE
};

class Atom
{
public:
	virtual std::string getName(void) const;
	virtual std::string getDescription(void) const;

	virtual void examine(ClientMob& client);
	virtual void process(void);

	ProcessingFlag processing = ProcessingFlag::no_process;
	Opacity opacity = Opacity::TRANSPARENT;

	void updateOpacity(Opacity newOpacity);
	void updateProcessing(ProcessingFlag newProcessing);

	void move(PositionInfo newPosition);

	/*
	* returns: false if movement blocked.
	*/
	virtual bool onMoveAttempt(Mob& mob);

	virtual char render(void);

	PositionInfo pi;

	operator PositionInfo(void)
	{
		return pi;
	}
};