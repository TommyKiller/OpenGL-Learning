#include "Character.h"

void Character::Use(std::weak_ptr<Ability> ability)
{
	if (ability.lock()->resource == this->Class.resource)
	{
		if (this->current_resource >= ability.lock()->cost)
		{
			current_resource -= ability.lock()->cost;
			AttackEvent(this, target, this->Hit());
		}
	}
	else if (ability.lock()->resource == Resource::None)
	{
		AttackEvent(this, target, this->Hit());
	}
}
