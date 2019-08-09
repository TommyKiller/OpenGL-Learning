#pragma once
#include <string>
#include "Resource.h"
#include "AttackType.h"
struct Ability
{
protected:
	Ability(char* const name, char* const tooltip, Source source);

	Ability(Ability&) = delete;

	Ability& operator=(Ability&) = delete;

public:
	std::string Name;
	std::string ToolTip;
	Source source;
};

