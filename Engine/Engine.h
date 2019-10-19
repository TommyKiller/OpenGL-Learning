#ifndef ENGINE_H
#define ENGINE_H
#include <memory>
#include "Window.h"
#include "InputHandler.h"
#include "FPSInput.h"

namespace System
{
	class Engine
	{
	public:
		static void Initialize(unsigned int maj_version, unsigned int min_version,
			int xpos, int ypos, int window_width, int window_height, const char* window_title, bool fullscreen_mode);

		// Delta time
		static void CalcDeltaTime();
		static double GetDeltaTime();

	private:
		static double delta_time;

		static void InitializeGLFW(unsigned int maj_version, unsigned int min_version);
		static void InitializeGLEW(Window& window);
		static void InitializeInput();
		static void InitializeScene();
	};

}

#endif
