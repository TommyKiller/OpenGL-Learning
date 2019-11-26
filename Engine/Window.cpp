#include "Window.h"

System::Window::Window()
	: window(nullptr), window_properties(0, 0, 0, 0)
{}

System::Window& System::Window::GetInstance()
{
	static Window window;

	return window;
}

void System::Window::Initialize(int xpos, int ypos, int window_width, int window_height, const char* window_title, bool fullscreen_mode)
{
	window_properties = WindowProperties(xpos, ypos, window_width, window_height);

	if (fullscreen_mode)
	{
		window = glfwCreateWindow(window_width, window_height, window_title, glfwGetPrimaryMonitor(), nullptr);
	}
	else
	{
		window = glfwCreateWindow(window_width, window_height, window_title, nullptr, nullptr);
		glfwSetWindowPos(window, xpos, ypos);
	}
	if (window == nullptr)
	{
		throw std::exception("Can not create GLFW window!");
		glfwTerminate();
	}

	glfwSetWindowUserPointer(window, this);
}

void System::Window::SetCallbacks(GLFWframebuffersizefun fb_cb_fun, GLFWwindowposfun wp_cb_fun, GLFWkeyfun k_cb_fun, GLFWcursorposfun cp_cb_fun)
{
	glfwSetFramebufferSizeCallback(window, fb_cb_fun);
	glfwSetWindowPosCallback(window, wp_cb_fun);
	glfwSetKeyCallback(window, k_cb_fun);
	glfwSetCursorPosCallback(window, cp_cb_fun);
}

void System::Window::FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	void* user_ptr = glfwGetWindowUserPointer(window);
	if (Window* window = static_cast<Window*>(user_ptr))
	{
		(*window->PollEvent(System::WindowEvents::WINDOW_FRAMEBUFFER_SIZE_CHANGED))(width, height);
	}
}

void System::Window::WindowPositionCallback(GLFWwindow* window, int xpos, int ypos)
{
	void* user_ptr = glfwGetWindowUserPointer(window);
	if (Window* window = static_cast<Window*>(user_ptr))
	{
		(*window->PollEvent(System::WindowEvents::WINDOW_POSITION_CHANGED))(xpos, ypos);
	}
}

std::unique_ptr<Events::Event<void, int, int>>& System::Window::PollEvent(System::WindowEvents event)
{
	return events[event];
}

void System::Window::SubscribeTo(WindowEvents event, Events::Delegate<void, int, int> delegate)
{
	(*this->events[event]) += delegate;
}

void System::Window::UnsubscribeTo(WindowEvents event, Events::Delegate<void, int, int> delegate)
{
	(*this->events[event]) -= delegate;
}

void System::Window::DisableCursor()
{
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void System::Window::HideCursor()
{
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}

void System::Window::EnableCursor()
{
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void System::Window::MakeCurrent()
{
	glfwMakeContextCurrent(window);
}

void System::Window::MakeNonCurrent()
{
	glfwMakeContextCurrent(nullptr);
}

void System::Window::SwapBuffers()
{
	glfwSwapBuffers(window);
}

bool System::Window::ShouldClose()
{
	return glfwWindowShouldClose(window);
}

void System::Window::Close()
{
	glfwSetWindowShouldClose(window, 1);
}

bool System::Window::IsFullscreen()
{
	return (glfwGetWindowMonitor(window) != nullptr);
}

void System::Window::SwitchScreenMode()
{
	if (IsFullscreen())
	{
		Windowed();
	}
	else
	{
		Fullscreen();
	}
}

void System::Window::Fullscreen()
{
	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);

	SaveWindowProperties();
	glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
}

void System::Window::Windowed()
{
	glfwSetWindowMonitor(window, nullptr, window_properties.xpos, window_properties.ypos, window_properties.width, window_properties.height, 0);
}

void System::Window::GetSize(int* width, int* height) const
{
	glfwGetWindowSize(window, width, height);
}

void System::Window::SetSize(int width, int height)
{
	glfwSetWindowSize(window, width, height);
}

void System::Window::GetFramebufferSize(int* framebuffer_width, int* framebuffer_height) const
{
	glfwGetFramebufferSize(window, framebuffer_width, framebuffer_height);
}

float System::Window::GetAspectRatio() const
{
	int width, height;
	GetSize(&width, &height);
	return ((float)width / (float)height);
}

void System::Window::Dispose()
{
	if (window != nullptr)
	{
		MakeNonCurrent();
		glfwDestroyWindow(window);
	}
}

System::Window::~Window()
{
	Dispose();
}

void System::Window::SaveWindowProperties()
{
	glfwGetWindowSize(window, &window_properties.width, &window_properties.height);
	glfwGetWindowPos(window, &window_properties.xpos, &window_properties.ypos);
}
