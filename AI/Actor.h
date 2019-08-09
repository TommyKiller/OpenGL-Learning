#pragma once
#include <memory>
#include "Event.h"
#include "Race.h"
#include "Class.h"


class Character
{
protected:
	Events::Event AttackEvent;
	Race Race;
	Class Class;
	unsigned int stamina;
	unsigned int strength;
	unsigned int agility;
	unsigned int dexterity;
	unsigned int spirit;
	unsigned int intellect;
	std::weak_ptr<ITarget> target;

public:
	Character();
};

