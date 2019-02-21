#ifndef FRAMEWORK_H
#define FRAMEWORK_H


#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <exception>
#include "Window.h"
#include "InputController.h"
#include "Render.h"
#include "Object.h"
#include "Scene.h"
#include "Camera.h"
#include "ShaderProgram.h"


namespace System
{
	void InitialiseGLFW(unsigned int maj_version, unsigned int min_version);

	void InitialiseGLEW(System::Window* window);
}


#endif
