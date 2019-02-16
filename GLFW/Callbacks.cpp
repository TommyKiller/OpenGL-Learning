#include "Callbacks.h"


void Callbacks::FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	Graphics::ReshapeViewport(0, 0, width, height);
}

void Callbacks::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, 1);
	}
	if (key == GLFW_KEY_W && action == GLFW_PRESS)
	{
		//Graphics::distance_to_pyramid += 0.1f;
	}
	if (key == GLFW_KEY_S && action == GLFW_PRESS)
	{
		//Graphics::distance_to_pyramid -= 0.1f;
	}
}
