#ifndef FRAMEWORK_H
#define FRAMEWORK_H


#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>
#include <exception>
#include <algorithm>
#include "Mesh.h"
#include "ShaderProgram.h"


extern glm::vec3 triangle_location;


namespace System
{
	void InitialiseGLFW();

	GLFWwindow* InitialiseWindow(int xpos, int ypos, int window_width, int window_height, bool fullscreen_mode,
		const char* window_title);

	void InitialiseGLEW(GLFWwindow* window);

	void SetUpGLSettings(glm::vec4 clearColor);
}


namespace Callbacks
{
	void FramebufferSizeCallback(GLFWwindow* window, int width, int height);

	void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
}


namespace Graphics
{
	void ReshapeViewport(GLint xpos, GLint ypos, GLsizei width, GLsizei height);
}


#endif
