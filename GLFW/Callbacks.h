#ifndef CALLBACKS_H
#define CALLBACKS_H


#include "Graphics.h"


namespace Callbacks
{
	void FramebufferSizeCallback(GLFWwindow* window, int width, int height);

	void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
}


#endif
