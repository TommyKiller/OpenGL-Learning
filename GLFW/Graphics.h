#ifndef GRAPHICS_H
#define GRAPHICS_H


#include "FrameworkDependencies.h"


namespace Graphics
{
	GLFWwindow* InitialiseWindow(int xpos, int ypos, int window_width, int window_height, bool fullscreen_mode, const char* window_title)
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

		GLFWwindow* window = fullscreen_mode ?
			glfwCreateWindow(window_width, window_height, window_title, glfwGetPrimaryMonitor(), nullptr) :
			glfwCreateWindow(window_width, window_height, window_title, nullptr, nullptr);

		glfwSetWindowPos(window, xpos, ypos);
		glfwMakeContextCurrent(window);

		if (window == nullptr)
		{
			throw std::exception("Can not create GLFW window!");
			glfwTerminate();
		}

		return window;
	}

	template<class T>
	GLuint InitialiseBuffer(GLenum target, std::vector<T>* data, GLenum usage)
	{
		GLuint buffer;
		glGenBuffers(1, &buffer);

		Graphics::BufferNewData(buffer, target, data, usage);

		return buffer;
	}

	template<class T>
	void BufferNewData(GLuint buffer, GLenum target, std::vector<T>* data, GLenum usage)
	{
		glBindBuffer(target, buffer);
		glBufferData(target, sizeof(T) * data->size(), data->data(), usage);
		glBindBuffer(target, 0);
	}

	template<class T>
	void BufferSubData(GLuint buffer, GLenum target, GLintptr offset, std::vector<T>* data)
	{
		glBindBuffer(target, buffer);
		glBufferSubData(target, offset, sizeof(float) * data->size(), data->data());
		glBindBuffer(target, 0);
	}

	GLuint InitializeVertexArray()
	{
		GLuint vertex_array;
		glGenVertexArrays(1, &vertex_array);
		return vertex_array;
	}

	void WriteToVAO(GLuint vao, GLuint buffer, GLenum target,
		int va_index, int size, GLenum type, GLboolean normalized, GLsizei stride, const void* shift)
	{
		glBindVertexArray(vao);
		glBindBuffer(target, buffer);
		glVertexAttribPointer(va_index, size, type, normalized, stride, shift);
		glBindBuffer(target, 0);
		glBindVertexArray(0);
	}

	void ReshapeViewport(GLint xpos, GLint ypos, GLsizei width, GLsizei height)
	{
		glViewport(xpos, ypos, width, height);
	}

	class Shader
	{
	public:
		Shader() = delete;

		Shader(Shader& shader)
		{
			ID = shader.ID;
		}

		Shader(std::unordered_map<std::string, GLenum> shaderSourcesList)
		{
			ID = InitialiseProgram(shaderSourcesList);
		}

		void bind()
		{
			glUseProgram(ID);
		}

		GLuint GetAttribLocation(std::string attribute_name)
		{
			return glGetAttribLocation(ID, attribute_name.c_str());
		}

		void SetUniform(std::string uniform_name, float uniform_value)
		{
			GLuint uniform_location = glGetUniformLocation(ID, uniform_name.c_str());
			glUniform1f(uniform_location, uniform_value);
		}

		void SetUniform(std::string uniform_name, int uniform_value1, int uniform_value2)
		{
			GLuint uniform_location = glGetUniformLocation(ID, uniform_name.c_str());
			glUniform2i(uniform_location, uniform_value1, uniform_value2);
		}

		void SetUniform(std::string uniform_name, int count, GLboolean transpose, glm::mat4 uniform_value)
		{
			GLuint uniform_location = glGetUniformLocation(ID, uniform_name.c_str());
			glUniformMatrix4fv(uniform_location, count, transpose, glm::value_ptr(uniform_value));
		}

		void unbind()
		{
			glUseProgram(0);
		}
	private:
		GLuint ID;

		GLuint CreateShader(GLenum shaderType, std::string fileName)
		{
			std::ifstream file(fileName);

			if (!file.is_open())
			{
				throw std::exception("Can not open file!");
			}

			std::string shaderSource;
			while (!file.eof())
			{
				char line[256];
				file.getline(line, 255);
				shaderSource = shaderSource + line + "\n";
			}
			const char* shaderSourceStr = shaderSource.c_str();

			GLuint shader = glCreateShader(shaderType);
			glShaderSource(shader, 1, &shaderSourceStr, nullptr);
			glCompileShader(shader);

			GLint status;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
			if (!status)
			{
				GLint infoLogLen;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLen);
				GLchar* infoLog = new GLchar[infoLogLen + 1];
				throw std::exception(infoLog);

				delete[] infoLog;
			}

			return shader;
		}

		GLuint InitialiseProgram(std::unordered_map<std::string, GLenum> shaderSourcesList)
		{
			std::vector<GLuint> shaderList;
			for (const auto& [key, value] : shaderSourcesList)
			{
				shaderList.push_back(CreateShader(value, key));
			}

			GLuint program = CreateProgram(shaderList);

			std::for_each(shaderList.begin(), shaderList.end(), glDeleteShader);

			return program;
		}

		GLuint CreateProgram(std::vector<GLuint> shaderList)
		{
			GLuint program = glCreateProgram();

			for (const auto& shader : shaderList)
			{
				glAttachShader(program, shader);
			}

			glLinkProgram(program);

			GLint status;
			glGetProgramiv(program, GL_LINK_STATUS, &status);
			if (!status)
			{
				GLint infoLogLen;
				glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLen);
				GLchar* infoLog = new GLchar[infoLogLen + 1];
				throw std::exception(infoLog);

				delete[] infoLog;
			}

			glValidateProgram(program);

			glGetProgramiv(program, GL_VALIDATE_STATUS, &status);
			if (!status)
			{
				GLint infoLogLen;
				glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLen);
				GLchar* infoLog = new GLchar[infoLogLen + 1];
				throw std::exception(infoLog);

				delete[] infoLog;
			}

			return program;
		}
	};
}


#endif
