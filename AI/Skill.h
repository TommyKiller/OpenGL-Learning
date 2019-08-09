#pragma once
#include "Ability.h"
struct Skill :	public Ability
{
public:
	Skill(Source source);

	Skill(Skill&) = delete;

	Skill& operator=(Skill&) = delete;
};

