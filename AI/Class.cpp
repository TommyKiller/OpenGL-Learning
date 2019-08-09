#include "Class.h"

std::list<std::shared_ptr<Class>> Class::Classes = {
	std::make_shared<Class>(Resource::Rage, std::list<std::shared_ptr<Ability>>{
		std::make_shared<Ability>(Resource::None, 0, Source::Physical, 0.0f)
	})
};

Class::Class(Resource resource, std::list<std::shared_ptr<Ability>> abilities)
	: resource(resource), abilities(abilities){}
