#ifndef FRAMEWORK_H
#define FRAMEWORK_H


#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <fstream>
#include <exception>
#include <unordered_map>
#include <vector>
#include <algorithm>

namespace System
{
	void InitialiseGLFW();
	void InitialiseGLEW(GLFWwindow* window);
}


namespace Callbacks
{
	void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
	void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
}


namespace Graphics
{
	GLFWwindow* InitialiseWindow(int xpos, int ypos, int window_width, int window_height, const char* window_title);

	GLuint InitialiseBuffer(GLenum target, std::vector<float>* data, GLenum usage);

	void BufferNewData(GLuint buffer, GLenum target, std::vector<float>* data, GLenum usage);

	void BufferSubData(GLuint buffer, GLenum target, GLintptr offset, std::vector<float>* data);

	GLuint InitializeVertexArray();

	void WriteToVAO(GLuint vao, GLuint buffer, GLenum target,
		int va_index, int size, GLenum type, GLboolean normalized, GLsizei stride, const void* shift);

	GLuint CreateShader(GLenum shaderType, std::string fileName);

	GLuint InitialiseProgram(std::unordered_map<std::string, GLenum> shaderSourcesList);

	GLuint CreateProgram(std::vector<GLuint> shaderList);

	void SetUniforms(GLuint program, float time_uniform, int window_width, int window_height);

	void ReshapeViewport(GLint xpos, GLint ypos, GLsizei width, GLsizei height);
}


#endif
