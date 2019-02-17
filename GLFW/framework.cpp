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

GLFWwindow* System::InitialiseWindow(int xpos, int ypos, int window_width, int window_height, bool fullscreen_mode, const char* window_title)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	GLFWwindow* window = fullscreen_mode ?
		glfwCreateWindow(window_width, window_height, window_title, glfwGetPrimaryMonitor(), nullptr) :
		glfwCreateWindow(window_width, window_height, window_title, nullptr, nullptr);

	glfwSetWindowPos(window, xpos, ypos);
	glfwMakeContextCurrent(window);

	if (window == nullptr)
	{
		throw std::exception("Can not create GLFW window!");
		glfwTerminate();
	}

	return window;
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
