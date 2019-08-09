#pragma once
#include "Ability.h"
struct Spell :	public Ability
{
private:
	Resource resource;
	unsigned int cost;

public:
	Spell(Source source, Resource resource, unsigned int cost);

	Spell(Spell&) = delete;

	Spell& operator=(Spell&) = delete;

	// Getters //
	Resource GetResource();
	unsigned int GetCost();
};

