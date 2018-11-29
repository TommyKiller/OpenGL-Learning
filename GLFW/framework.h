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


namespace Graphics
{
	GLFWwindow *InitializeWindow(int window_width, int window_height, const char *window_title);

	GLuint InitializeBuffer(GLenum target, std::vector<float> *data, GLenum usage);

	void BufferData(GLuint buffer, GLenum target, std::vector<float> *data, GLenum usage);

	GLuint InitializeVertexArray();

	void WriteToVAO(GLuint vao, GLuint buffer, GLenum target,
		int va_index, int size, GLenum type, GLboolean normalized, GLsizei stride, const void *shift);

	GLuint CreateShader(GLenum shaderType, std::string fileName);

	GLuint InitializeProgram(std::unordered_map<std::string, GLenum> shaderSourcesList);

	GLuint CreateProgram(std::vector<GLuint> shaderList);

	void Reshape(GLint xpos, GLint ypos, GLsizei width, GLsizei height);
}


#endif
