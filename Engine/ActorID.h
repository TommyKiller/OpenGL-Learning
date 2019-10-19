#ifndef ACTORID_H
#define ACTORID_H
#include <string>

namespace Graphics
{
	class ActorID
	{
	public:
		ActorID(std::string id);

		bool operator==(ActorID& id) const;

		bool operator!=(ActorID& id) const;

	private:
		std::string id;

	};
}

#endif
