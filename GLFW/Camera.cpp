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

void Engine::Camera::FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	int xpos, ypos;
	glfwGetWindowPos(window, &xpos, &ypos);
	glViewport(xpos, ypos, width, height);
}

Engine::Camera::Camera()
{}

Engine::Camera::~Camera()
{
	Dispose();
}
