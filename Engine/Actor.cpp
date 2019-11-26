#include "Actor.h"

Graphics::Actor::Actor(std::string id, Position position)
	: id(id), position(position)
{
	(*actor_events[ActorEvents::ACTOR_SPAWNED])();
}

Graphics::ActorID Graphics::Actor::GetID()
{
	return id;
}

void Graphics::Actor::AdjustForward(float speed)
{
	position.Pos += position.Front * GetVelolcity(speed);
	(*actor_movements[ActorMovements::ACTOR_ADJUSTED_FORWARD])(speed);
}

void Graphics::Actor::AdjustBackward(float speed)
{
	position.Pos -= position.Front * GetVelolcity(speed);
	(*actor_movements[ActorMovements::ACTOR_ADJUSTED_BACKWARD])(speed);
}

void Graphics::Actor::AdjustRight(float speed)
{
	position.Pos += position.Right * GetVelolcity(speed);
	(*actor_movements[ActorMovements::ACTOR_ADJUSTED_RIGHT])(speed);
}

void Graphics::Actor::AdjustLeft(float speed)
{
	position.Pos -= position.Right * GetVelolcity(speed);
	(*actor_movements[ActorMovements::ACTOR_ADJUSTED_LEFT])(speed);
}

void Graphics::Actor::AdjustUp(float speed)
{
	position.Pos += position.Up * GetVelolcity(speed);
	(*actor_movements[ActorMovements::ACTOR_ADJUSTED_UP])(speed);
}

void Graphics::Actor::AdjustDown(float speed)
{
	position.Pos -= position.Up * GetVelolcity(speed);
	(*actor_movements[ActorMovements::ACTOR_ADJUSTED_DOWN])(speed);
}

void Graphics::Actor::Move()
{
	(*actor_events[ActorEvents::ACTOR_MOVED])();
}

GLfloat Graphics::Actor::GetVelolcity(float speed)
{
	return System::Engine::GetDeltaTime() * speed;
}
// Subscription in events //
void Graphics::Actor::SubscribeTo(ActorEvents event, Events::Delegate<void> delegate)
{
	(*actor_events[event]) += delegate;
}
void Graphics::Actor::SubscribeTo(ActorMovements event, Events::Delegate<void, float> delegate)
{
	(*actor_movements[event]) += delegate;
}
//------------------------//
void Graphics::Actor::UnsubscribeTo(ActorEvents event, Events::Delegate<void> delegate)
{
	(*actor_events[event]) -= delegate;
}
void Graphics::Actor::UnsubscribeTo(ActorMovements event, Events::Delegate<void, float> delegate)
{
	(*actor_movements[event]) -= delegate;
}
// END Subscription on events //

Graphics::Actor::~Actor()
{
	(*actor_events[ActorEvents::ACTOR_DESTROYED])();
}
