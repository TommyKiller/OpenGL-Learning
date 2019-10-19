#include "Engine.h"

double System::Engine::delta_time = 0.0f;

void System::Engine::Initialize(unsigned int maj_version, unsigned int min_version,
	int xpos, int ypos, int window_width, int window_height, const char* window_title, bool fullscreen_mode)
{
	InitializeGLFW(maj_version, min_version);
	Window::GetInstance().Initialize(xpos, ypos, window_width, window_height, window_title, fullscreen_mode);
	InitializeGLEW(Window::GetInstance());
	Window::GetInstance().MakeCurrent();
}

void System::Engine::CalcDeltaTime()
{
	static double last = 0.0f;
	double now = glfwGetTime();
	delta_time = now - last;
	last = now;
}

double System::Engine::GetDeltaTime()
{
	return delta_time;
}

void System::Engine::InitializeGLFW(unsigned int maj_version, unsigned int min_version)
{
	if (!glfwInit())
	{
		throw std::exception("Can not initialise GLFW!");
		glfwTerminate();
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, maj_version);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, min_version);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
}

void System::Engine::InitializeGLEW(Window& window)
{
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		throw std::exception("Can not initialize GLEW!");
		window.Dispose();
		glfwTerminate();
	}
}
