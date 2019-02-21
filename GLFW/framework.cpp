#include "framework.h"


// System //
void System::InitialiseGLFW()
{
	if (!glfwInit())
	{
		throw std::exception("Can not initialize GLFW!");
		glfwTerminate();
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	glfwSetTime(0);
}

void System::InitialiseGLEW(System::Window* window)
{
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		throw std::exception("Can not initialize GLEW!");
		delete window;
		glfwTerminate();
	}
}
