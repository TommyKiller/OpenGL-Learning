#pragma once
#include <list>
#include <memory>
#include <string>
#include "Ability.h"


struct Class
{
public:
	Class(char* const name, char* const tooltip, Resource resource, std::list<std::shared_ptr<Ability>> abilities);

	std::string Name;
	std::string ToolTip;
	Resource resource;
	std::list<std::shared_ptr<Ability>> abilities;

	static std::list<std::shared_ptr<Class>> Classes;
};

