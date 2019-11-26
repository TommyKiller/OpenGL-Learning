#ifndef ACTOR_H
#define ACTOR_H
#include <map>
#include <memory>
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include "utilities/make_unordered_map.h"
#include "Shader.h"
#include "ActorID.h"
#include "ActorEvents.h"
#include "utilities/Event.h"
#include "Position.h"
#include "Engine.h"

namespace Graphics
{
	class Actor
	{
	public:
		Actor(std::string id, Position position);

		ActorID GetID();

		// Movement
		virtual void AdjustForward(float speed);
		virtual void AdjustBackward(float speed);
		virtual void AdjustRight(float speed);
		virtual void AdjustLeft(float speed);
		virtual void AdjustUp(float speed);
		virtual void AdjustDown(float speed);
		virtual void Move();
		GLfloat GetVelolcity(float speed);

		// Subscription
		void SubscribeTo(ActorEvents event, Events::Delegate<void> delegate);
		void SubscribeTo(ActorMovements event, Events::Delegate<void, float> delegate);
		void UnsubscribeTo(ActorEvents event, Events::Delegate<void> delegate);
		void UnsubscribeTo(ActorMovements event, Events::Delegate<void, float> delegate);

		// Termination
		virtual ~Actor();

	protected:
		ActorID id;
		Position position;

		std::unordered_map<ActorEvents, std::unique_ptr<Events::Event<void>>> actor_events = make_unordered_map
		(
			std::make_pair(ActorEvents::ACTOR_SPAWNED,		std::make_unique<Events::Event<void>>()),
			std::make_pair(ActorEvents::ACTOR_DESTROYED,	std::make_unique<Events::Event<void>>()),
			std::make_pair(ActorEvents::ACTOR_MOVED,		std::make_unique<Events::Event<void>>())
		);
		std::unordered_map<ActorMovements, std::unique_ptr<Events::Event<void, float>>> actor_movements = make_unordered_map
		(
			std::make_pair(ActorMovements::ACTOR_ADJUSTED_FORWARD, std::make_unique<Events::Event<void, float>>()),
			std::make_pair(ActorMovements::ACTOR_ADJUSTED_BACKWARD, std::make_unique<Events::Event<void, float>>()),
			std::make_pair(ActorMovements::ACTOR_ADJUSTED_RIGHT, std::make_unique<Events::Event<void, float>>()),
			std::make_pair(ActorMovements::ACTOR_ADJUSTED_LEFT, std::make_unique<Events::Event<void, float>>()),
			std::make_pair(ActorMovements::ACTOR_ADJUSTED_UP, std::make_unique<Events::Event<void, float>>()),
			std::make_pair(ActorMovements::ACTOR_ADJUSTED_DOWN, std::make_unique<Events::Event<void, float>>())
		);
	};
}

#endif
