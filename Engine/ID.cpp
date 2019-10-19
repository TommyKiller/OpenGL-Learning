#include "ID.h"

bool Identification::ID::operator==(Identification::ID& id) const
{
	return (this->id == id.id);
}

bool Identification::ID::operator!=(Identification::ID& id) const
{
	return (this->id != id.id);
}
