#ifndef FRAMEWORK_H
#define FRAMEWORK_H


#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>
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
	GLFWwindow* InitialiseWindow(int xpos, int ypos, int window_width, int window_height, bool fullscreen_mode, const char* window_title);

	GLuint InitialiseBuffer(GLenum target, std::vector<float>* data, GLenum usage);

	void BufferNewData(GLuint buffer, GLenum target, std::vector<float>* data, GLenum usage);

	void BufferSubData(GLuint buffer, GLenum target, GLintptr offset, std::vector<float>* data);

	GLuint InitializeVertexArray();

	void WriteToVAO(GLuint vao, GLuint buffer, GLenum target,
		int va_index, int size, GLenum type, GLboolean normalized, GLsizei stride, const void* shift);

	void ReshapeViewport(GLint xpos, GLint ypos, GLsizei width, GLsizei height);

	class Shader
	{
	public:
		Shader() = delete;

		Shader(Shader& shader);

		Shader(std::unordered_map<std::string, GLenum> shaderSourcesList);

		void bind();

		GLuint GetAttribLocation(std::string attribute_name);

		void SetUniform(std::string uniform_name, float uniform_value);

		void SetUniform(std::string uniform_name, int uniform_value1, int uniform_value2);

		void SetUniform(std::string uniform_name, int count, GLboolean transpose, glm::mat4 uniform_value);

		void unbind();
	private:
		GLuint ID;

		GLuint CreateShader(GLenum shaderType, std::string fileName);

		GLuint InitialiseProgram(std::unordered_map<std::string, GLenum> shaderSourcesList);

		GLuint CreateProgram(std::vector<GLuint> shaderList);
	};
}


#endif
