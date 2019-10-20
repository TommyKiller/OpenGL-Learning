#ifndef ACTOREVENTS_H
#define ACTOREVENTS_H

namespace Graphics
{
	enum class ActorEvents
	{
		EVENT_ACTOR_SPAWNED,
		EVENT_ACTOR_DESTROYED,
		EVENT_ACTOR_ADJUSTED_FORWARD,
		EVENT_ACTOR_ADJUSTED_BACKWARD,
		EVENT_ACTOR_ADJUSTED_RIGHT,
		EVENT_ACTOR_ADJUSTED_LEFT,
		EVENT_ACTOR_ADJUSTED_UP,
		EVENT_ACTOR_ADJUSTED_DOWN,
		EVENT_ACTOR_ADJUSTED_YAW,
		EVENT_ACTOR_ADJUSTED_PITCH,
		EVENT_ACTOR_MOVED
	};
}

#endif