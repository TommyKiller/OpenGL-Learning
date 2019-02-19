#ifndef FRAMEWORK_H
#define FRAMEWORK_H


#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <exception>
#include "Mesh.h"
#include "ShaderProgram.h"
#include "Window.h"
#include "InputController.h"


namespace System
{
	void InitialiseGLFW();

	void InitialiseGLEW(Graphics::Window* window);

	void SetUpGLSettings(glm::vec4 clearColor);
}

namespace Callbacks
{
	void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
}

namespace Graphics
{
	void ReshapeViewport(GLint xpos, GLint ypos, GLsizei width, GLsizei height);
}


#endif
