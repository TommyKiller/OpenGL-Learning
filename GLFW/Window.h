#ifndef WINDOW_H
#define WINDOW_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <exception>


namespace Graphics
{
	class Window
	{
	public:
		Window(int xpos, int ypos, int window_width, int window_height, const char* window_title, bool fullscreen_mode);

		void MakeCurrent();

		void SetCallbacks(GLFWframebuffersizefun fb_cb_fun, GLFWkeyfun k_cb_fun);

		void SwapBuffers();

		bool ShouldClose();

		bool IsFullscreen();

		void SwapBuffers();

		void Fullscreen();

		void WindowedFullscreen();

		void Windowed();

		void GetSize(int* width, int* height) const;

		void SetSize(int width, int height);

		void GetFramebufferSize(int* framebuffer_width, int* framebuffer_height) const;

		void Close();

		void Dispose();

		~Window();

	private:
		struct WindowMode
		{
			int xpos;
			int ypos;
			int width;
			int height;
			int refreshRate;
		};

		GLFWwindow* window;
		WindowMode windowed_mode;

		void SaveWindowedModeSettings();
	};
}


#endif
