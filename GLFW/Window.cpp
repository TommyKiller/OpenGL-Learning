#include "Window.h"

Graphics::Window::Window(int xpos, int ypos, int window_width, int window_height, const char* window_title, bool fullscreen_mode)
{
	window = fullscreen_mode ?
		glfwCreateWindow(window_width, window_height, window_title, glfwGetPrimaryMonitor(), nullptr) :
		glfwCreateWindow(window_width, window_height, window_title, nullptr, nullptr);

	if (window == nullptr)
	{
		throw std::exception("Can not create GLFW window!");
		glfwTerminate();
	}

	glfwSetWindowPos(window, xpos, ypos);

	SaveWindowedModeProperties();
}

void Graphics::Window::MakeCurrent()
{
	if (window != nullptr)
	{
		glfwMakeContextCurrent(window);
	}
}

void Graphics::Window::SetCallbacks(GLFWframebuffersizefun fb_cb_fun, GLFWkeyfun k_cb_fun)
{
	glfwSetFramebufferSizeCallback(window, fb_cb_fun);
	glfwSetKeyCallback(window, k_cb_fun);
}

void Graphics::Window::SwapBuffers()
{
	glfwSwapBuffers(window);
}

bool Graphics::Window::ShouldClose()
{
	return glfwWindowShouldClose(window);
}

bool Graphics::Window::IsFullscreen()
{
	return (glfwGetWindowMonitor(window) != nullptr);
}

void Graphics::Window::Fullscreen()
{
	if (!IsFullscreen() && (window != nullptr))
	{
		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* mode = glfwGetVideoMode(monitor);

		SaveWindowedModeProperties();
		glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
	}
}

void Graphics::Window::Windowed()
{
	if (IsFullscreen() && (window != nullptr))
	{
		glfwSetWindowMonitor(window, nullptr, windowed_mode_properties.xpos, windowed_mode_properties.ypos, windowed_mode_properties.width, windowed_mode_properties.height, windowed_mode_properties.refreshRate);
	}
}

void Graphics::Window::GetSize(int* width, int* height) const
{
	if (window != nullptr)
	{
		glfwGetWindowSize(window, width, height);
	}
}

void Graphics::Window::SetSize(int width, int height)
{
	if (window != nullptr)
	{
		glfwSetWindowSize(window, width, height);
	}
}

void Graphics::Window::GetFramebufferSize(int* framebuffer_width, int* framebuffer_height) const
{
	if (window != nullptr)
	{
		glfwGetFramebufferSize(window, framebuffer_width, framebuffer_height);
	}
}

void Graphics::Window::Close()
{
	if (window != nullptr)
	{
		glfwSetWindowShouldClose(window, 1);
	}
}

void Graphics::Window::Dispose()
{
	if (window != nullptr)
	{
		glfwDestroyWindow(window);
	}
}

Graphics::Window::~Window()
{
	Dispose();
}

void Graphics::Window::SaveWindowedModeProperties()
{
	glfwGetWindowSize(window, &windowed_mode_properties.width, &windowed_mode_properties.height);
	glfwGetWindowPos(window, &windowed_mode_properties.xpos, &windowed_mode_properties.ypos);
	windowed_mode_properties.refreshRate = glfwGetVideoMode(glfwGetPrimaryMonitor())->refreshRate;
}
