#ifndef FRAMEWORK_H
#define FRAMEWORK_H


#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <exception>
#include "Mesh.h"
#include "ShaderProgram.h"
#include "Window.h"
#include "InputController.h"
#include "Camera.h"
#include "Scene.h"
#include "Renderer.h"


namespace System
{
	void InitialiseGLFW();

	void InitialiseGLEW(System::Window* window);

	void SetUpGLSettings(glm::vec4 clearColor);
}


#endif
