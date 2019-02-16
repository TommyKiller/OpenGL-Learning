#include "System.h"


void System::InitialiseGLFW()
{
	if (!glfwInit())
	{
		throw std::exception("Can not initialize GLFW!");
		glfwTerminate();
	}
}

void System::InitialiseGLEW(GLFWwindow* window)
{
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		throw std::exception("Can not initialize GLEW!");
		glfwDestroyWindow(window);
		glfwTerminate();
	}
}
