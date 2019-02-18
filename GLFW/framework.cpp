#include "framework.h"


glm::vec3 triangle_location(0.0f, 0.0f, -2.0f);


// System //
void System::InitialiseGLFW()
{
	if (!glfwInit())
	{
		throw std::exception("Can not initialize GLFW!");
		glfwTerminate();
	}
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

void Callbacks::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, 1);
	}
	if (key == GLFW_KEY_W && ((action == GLFW_REPEAT) || (action == GLFW_PRESS)))
	{
		triangle_location.z += 0.03f;
	}
	if (key == GLFW_KEY_S && ((action == GLFW_REPEAT) || (action == GLFW_PRESS)))
	{
		triangle_location.z -= 0.03f;
	}
	if (key == GLFW_KEY_A && ((action == GLFW_REPEAT) || (action == GLFW_PRESS)))
	{
		triangle_location.x += 0.03f;
	}
	if (key == GLFW_KEY_D && ((action == GLFW_REPEAT) || (action == GLFW_PRESS)))
	{
		triangle_location.x -= 0.03f;
	}
	if (key == GLFW_KEY_LEFT_CONTROL && ((action == GLFW_REPEAT) || (action == GLFW_PRESS)))
	{
		triangle_location.y += 0.03f;
	}
	if (key == GLFW_KEY_SPACE && ((action == GLFW_REPEAT) || (action == GLFW_PRESS)))
	{
		triangle_location.y -= 0.03f;
	}
}


// Graphics //
void Graphics::ReshapeViewport(GLint xpos, GLint ypos, GLsizei width, GLsizei height)
{
	glViewport(xpos, ypos, width, height);
}
