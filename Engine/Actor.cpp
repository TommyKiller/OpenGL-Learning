#include "Actor.h"

Graphics::Actor::Actor(std::string id, Position position)
	: id(id), position(position)
{
	(*events[ActorEvents::EVENT_ACTOR_SPAWNED])();
}

Graphics::ActorID Graphics::Actor::GetID()
{
	return id;
}

void Graphics::Actor::AdjustForward(float speed)
{
	position.Pos += position.Front * GetVelolcity(speed);
	(*events[ActorEvents::EVENT_ACTOR_ADJUSTED_FORWARD])();
}

void Graphics::Actor::AdjustBackward(float speed)
{
	position.Pos -= position.Front * GetVelolcity(speed);
	(*events[ActorEvents::EVENT_ACTOR_ADJUSTED_BACKWARD])();
}

void Graphics::Actor::AdjustRight(float speed)
{
	position.Pos += position.Right * GetVelolcity(speed);
	(*events[ActorEvents::EVENT_ACTOR_ADJUSTED_RIGHT])();
}

void Graphics::Actor::AdjustLeft(float speed)
{
	position.Pos -= position.Right * GetVelolcity(speed);
	(*events[ActorEvents::EVENT_ACTOR_ADJUSTED_LEFT])();
}

void Graphics::Actor::AdjustUp(float speed)
{
	position.Pos += position.Up * GetVelolcity(speed);
	(*events[ActorEvents::EVENT_ACTOR_ADJUSTED_UP])();
}

void Graphics::Actor::AdjustDown(float speed)
{
	position.Pos -= position.Up * GetVelolcity(speed);
	(*events[ActorEvents::EVENT_ACTOR_ADJUSTED_DOWN])();
}

void Graphics::Actor::Move()
{
	(*events[ActorEvents::EVENT_ACTOR_MOVED])();
}

GLfloat Graphics::Actor::GetVelolcity(float speed)
{
	return System::Engine::GetDeltaTime() * speed;
}

void Graphics::Actor::SubscribeTo(ActorEvents event, Events::Delegate delegate)
{
	(*events[event]) += delegate;
}

void Graphics::Actor::UnsubscribeTo(ActorEvents event, Events::Delegate delegate)
{
	(*events[event]) -= delegate;
}

Graphics::Actor::~Actor()
{
	(*events[ActorEvents::EVENT_ACTOR_DESTROYED])();
}
