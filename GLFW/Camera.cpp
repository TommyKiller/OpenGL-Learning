#include "Camera.h"

Engine::Camera* Engine::Camera::instance = nullptr;

Engine::Camera* Engine::Camera::GetInstance()
{
	return instance;
}

void Engine::Camera::Initialise()
{
	if (!instance)
	{
		instance = new Camera();
	}
}

void Engine::Camera::Dispose()
{
	delete instance;
}

Engine::Camera::Camera()
{}

Engine::Camera::~Camera()
{
	Dispose();
}
