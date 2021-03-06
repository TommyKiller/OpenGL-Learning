#ifndef ACTOREVENTS_H
#define ACTOREVENTS_H

namespace Graphics
{
	enum class ActorEvents
	{
		ACTOR_SPAWNED,
		ACTOR_DESTROYED,
		ACTOR_MOVED
	};

	enum class ActorMovements
	{
		ACTOR_ADJUSTED_FORWARD,
		ACTOR_ADJUSTED_BACKWARD,
		ACTOR_ADJUSTED_RIGHT,
		ACTOR_ADJUSTED_LEFT,
		ACTOR_ADJUSTED_UP,
		ACTOR_ADJUSTED_DOWN,
		ACTOR_ADJUSTED_YAW,
		ACTOR_ADJUSTED_PITCH,
	};
}

#endif
