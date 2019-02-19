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
}

void System::InitialiseGLEW(Graphics::Window* window)
{
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		throw std::exception("Can not initialize GLEW!");
		delete window;
		glfwTerminate();
	}
}

void System::SetUpGLSettings(glm::vec4 clearColor)
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
	glfwSetTime(0);
}


// Callbacks //
void Callbacks::FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	Graphics::ReshapeViewport(0, 0, width, height);
}


// Graphics //
void Graphics::ReshapeViewport(GLint xpos, GLint ypos, GLsizei width, GLsizei height)
{
	glViewport(xpos, ypos, width, height);
}
