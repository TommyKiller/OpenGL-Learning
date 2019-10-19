#ifndef ACTOR_H
#define ACTOR_H
#include <map>
#include <memory>
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include "Shader.h"
#include "ActorID.h"
#include "ActorEvents.h"
#include "Event.h"
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
		void SubscribeTo(ActorEvents event, Events::Delegate delegate);
		void UnsubscribeTo(ActorEvents event, Events::Delegate delegate);

		// Termination
		virtual ~Actor();

	protected:
		ActorID id;
		Position position;

		std::map<ActorEvents, std::shared_ptr<Events::Event>> events
		{
			std::pair<ActorEvents, std::shared_ptr<Events::Event>>{ ActorEvents::EVENT_ACTOR_SPAWNED, std::make_shared<Events::Event>() },
			std::pair<ActorEvents, std::shared_ptr<Events::Event>>{ ActorEvents::EVENT_ACTOR_ADJUSTED_FORWARD, std::make_shared<Events::Event>() },
			std::pair<ActorEvents, std::shared_ptr<Events::Event>>{ ActorEvents::EVENT_ACTOR_ADJUSTED_BACKWARD, std::make_shared<Events::Event>() },
			std::pair<ActorEvents, std::shared_ptr<Events::Event>>{ ActorEvents::EVENT_ACTOR_ADJUSTED_RIGHT, std::make_shared<Events::Event>() },
			std::pair<ActorEvents, std::shared_ptr<Events::Event>>{ ActorEvents::EVENT_ACTOR_ADJUSTED_LEFT, std::make_shared<Events::Event>() },
			std::pair<ActorEvents, std::shared_ptr<Events::Event>>{ ActorEvents::EVENT_ACTOR_ADJUSTED_UP, std::make_shared<Events::Event>() },
			std::pair<ActorEvents, std::shared_ptr<Events::Event>>{ ActorEvents::EVENT_ACTOR_ADJUSTED_DOWN, std::make_shared<Events::Event>() },
			std::pair<ActorEvents, std::shared_ptr<Events::Event>>{ ActorEvents::EVENT_ACTOR_MOVED, std::make_shared<Events::Event>() }
		};
	};
}

#endif
