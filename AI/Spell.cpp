#include "Spell.h"

Spell::Spell(Source source, Resource resource, unsigned int cost)
	: Ability(source), resource(resource), cost(cost){}

Resource Spell::GetResource()
{
	return resource;
}

unsigned int Spell::GetCost()
{
	return cost;
}
