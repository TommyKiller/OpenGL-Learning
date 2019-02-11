#include "framework.h"


// System //
void System::InitialiseGLFW()
{
	if (!glfwInit())
	{
		throw std::exception("Can not initialize GLFW!");
		glfwTerminate();
	}
}

void System::InitialiseGLEW(GLFWwindow* window)
{
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		throw std::exception("Can not initialize GLEW!");
		glfwDestroyWindow(window);
		glfwTerminate();
	}
}


// Callbacks //
void Callbacks::FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	Graphics::ReshapeViewport(0, 0, width, height);
}

void Callbacks::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, 1);
	}
}


// Graphics //
GLFWwindow* Graphics::InitialiseWindow(int xpos, int ypos, int window_width, int window_height, bool fullscreen_mode, const char* window_title)
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

GLuint Graphics::InitialiseBuffer(GLenum target, std::vector<float>* data, GLenum usage)
{
	GLuint buffer;
	glGenBuffers(1, &buffer);

	Graphics::BufferNewData(buffer, target, data, usage);

	return buffer;
}

void Graphics::BufferNewData(GLuint buffer, GLenum target, std::vector<float>* data, GLenum usage)
{
	glBindBuffer(target, buffer);
	glBufferData(target, sizeof(float)*  data->size(), data->data(), usage);
	glBindBuffer(target, 0);
}

void Graphics::BufferSubData(GLuint buffer, GLenum target, GLintptr offset, std::vector<float>* data)
{
	glBindBuffer(target, buffer);
	glBufferSubData(target, offset, sizeof(float)*  data->size(), data->data());
	glBindBuffer(target, 0);
}

GLuint Graphics::InitializeVertexArray()
{
	GLuint vertex_array;
	glGenVertexArrays(1, &vertex_array);
	return vertex_array;
}

void Graphics::WriteToVAO(GLuint vao, GLuint buffer, GLenum target,
	int va_index, int size, GLenum type, GLboolean normalized, GLsizei stride, const void* shift)
{
	glBindVertexArray(vao);
	glBindBuffer(target, buffer);
	glVertexAttribPointer(va_index, size, type, normalized, stride, shift);
	glBindBuffer(target, 0);
	glBindVertexArray(0);
}

GLuint Graphics::CreateShader(GLenum shaderType, std::string fileName)
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
		file.getline(line , 255);
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

GLuint Graphics::InitialiseProgram(std::unordered_map<std::string, GLenum> shaderSourcesList)
{
	std::vector<GLuint> shaderList;
	for (const auto &[key, value] : shaderSourcesList)
	{
		shaderList.push_back(CreateShader(value, key));
	}

	GLuint program = CreateProgram(shaderList);

	std::for_each(shaderList.begin(), shaderList.end(), glDeleteShader);

	return program;
}

GLuint Graphics::CreateProgram(std::vector<GLuint> shaderList)
{
	GLuint program = glCreateProgram();

	for (const auto &shader : shaderList)
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

void Graphics::SetUniforms(GLuint program, GLfloat time_uniform, int* resolution)
{
	GLuint time_uniform_location = glGetUniformLocation(program, "time");
	glUniform1f(time_uniform_location, time_uniform);
	GLuint resolution_uniform_location = glGetUniformLocation(program, "resolution");
	glUniform2iv(resolution_uniform_location, 1, resolution);
}

void Graphics::ReshapeViewport(GLint xpos, GLint ypos, GLsizei width, GLsizei height)
{
	glViewport(xpos, ypos, width, height);
}
