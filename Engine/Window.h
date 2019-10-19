#ifndef WINDOW_H
#define WINDOW_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <exception>
#include "InputController.h"


namespace System
{
	enum class WindowEvents
	{
		WINDOW_FRAMEBUFFER_SIZE_CHANGED,
		WINDOW_POSITION_CHANGED
	};

	class Window
	{
	public:
		static Window& GetInstance();

		void Initialize(int xpos, int ypos, int window_width, int window_height, const char* window_title, bool fullscreen_mode);

		// Callbacks
		void SetCallbacks(GLFWframebuffersizefun fb_cb_fun, GLFWwindowposfun wp_cb_fun, GLFWkeyfun k_cb_fun, GLFWcursorposfun cp_cb_fun); // HAS TO BE REDISIGNED
		static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
		static void WindowPositionCallback(GLFWwindow* window, int xpos, int ypos);

		// Events
		std::shared_ptr<Events::Event>& PollEvent(System::WindowEvents event);
		void SubscribeTo(WindowEvents event, Events::Delegate delegate);
		void UnsubscribeTo(WindowEvents event, Events::Delegate delegate);

		// Cursor
		void DisableCursor();
		void HideCursor();
		void EnableCursor();

		// Window control
		void MakeCurrent(); // HERE BIND TO ALL INPUT EVENTS
		void MakeNonCurrent(); // HERE UNBIND TO ALL INPUT EVENTS
		void SwapBuffers();
		bool ShouldClose();
		void Close();

		// Screen modes
		bool IsFullscreen();
		void SwitchScreenMode();
		void Fullscreen();
		void Windowed();

		// Window settings
		void SetSize(int width, int height);
		void GetSize(int* width, int* height) const;
		void GetFramebufferSize(int* framebuffer_width, int* framebuffer_height) const;
		float GetAspectRatio() const;

		void Dispose();
		~Window();

	private:
		struct WindowProperties
		{
			WindowProperties(int xpos, int ypos, int width, int height)
				: xpos(xpos), ypos(ypos), width(width), height(height)
			{}

			int xpos;
			int ypos;
			int width;
			int height;
		};

		std::map<System::WindowEvents, std::shared_ptr<Events::Event>> events
		{
			{ WindowEvents::WINDOW_FRAMEBUFFER_SIZE_CHANGED, std::make_shared<Events::Event>() },
			{ WindowEvents::WINDOW_POSITION_CHANGED, std::make_shared<Events::Event>() }
		};

		GLFWwindow* window;
		WindowProperties window_properties;

		void SaveWindowProperties();

		Window();
		Window(Window&) = delete;
		Window& operator=(Window&) = delete;
	};
}


#endif
