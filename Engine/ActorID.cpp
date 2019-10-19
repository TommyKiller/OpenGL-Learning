#include "ActorID.h"

Graphics::ActorID::ActorID(std::string id)
	: id(id)
{}

bool Graphics::ActorID::operator==(ActorID& id) const
{
	return (this->id == id.id);
}

bool Graphics::ActorID::operator!=(ActorID& id) const
{
	return (this->id != id.id);
}
