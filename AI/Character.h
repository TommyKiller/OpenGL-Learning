#pragma once
#include <memory>
#include "Hit.h"
#include "Event.h"
#include "Race.h"
#include "Class.h"


class Character
{
protected:
	// Events //
	Events::Event AttackEvent;

	// ?? //
	std::weak_ptr<Race> Race;
	std::weak_ptr<Class> Class;
	std::list<std::weak_ptr<Ability>> SpellBook;

	// Stats //
	unsigned int current_resource;
	unsigned int max_resource;
	unsigned int stamina;
	unsigned int strength;
	unsigned int agility;
	unsigned int dexterity;
	unsigned int spirit;
	unsigned int intellect;

	// Logic //
	std::weak_ptr<Character> target;

	void Use(std::weak_ptr<Ability> ability);

	Hit Hit();

public:
	Character();
};

