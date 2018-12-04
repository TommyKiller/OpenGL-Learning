#include "framework.h"


using namespace Graphics;
GLFWwindow *Graphics::InitializeWindow(int window_width, int window_height, const char *window_title)
{
	if (!glfwInit())
	{
		throw std::exception("Can not initialize GLFW!");
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	GLFWwindow *window = glfwCreateWindow(window_width, window_height, window_title, nullptr, nullptr);
	glfwSetWindowPos(window, 0, 0);
	glfwMakeContextCurrent(window);

	if (window == nullptr)
	{
		glfwTerminate();
		throw std::exception("Can not create GLFW window!");
	}

	int fb_width, fb_height;
	glfwGetFramebufferSize(window, &fb_width, &fb_height);
	Reshape(0, 0, fb_width, fb_height);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		throw std::exception("Can not initialize GLEW!");
	}

	return window;
}

GLuint Graphics::InitializeBuffer(GLenum target, std::vector<float> *data, GLenum usage)
{
	GLuint buffer;
	glGenBuffers(1, &buffer);

	BufferNewData(buffer, target, data, usage);

	return buffer;
}

void Graphics::BufferNewData(GLuint buffer, GLenum target, std::vector<float> *data, GLenum usage)
{
	glBindBuffer(target, buffer);
	glBufferData(target, sizeof(float) * data->size(), data->data(), usage);
	glBindBuffer(target, 0);
}

void Graphics::BufferAdjustData(GLuint buffer, GLenum target, GLintptr offset, std::vector<float> *data)
{
	glBindBuffer(target, buffer);
	glBufferSubData(target, offset, sizeof(float) * data->size(), data->data());
	glBindBuffer(target, 0);
}

GLuint Graphics::InitializeVertexArray()
{
	GLuint vertex_array;
	glGenVertexArrays(1, &vertex_array);
	return vertex_array;
}

void Graphics::WriteToVAO(GLuint vao, GLuint buffer, GLenum target,
	int va_index, int size, GLenum type, GLboolean normalized, GLsizei stride, const void *shift)
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
	const char *shaderSourceStr = shaderSource.c_str();

	GLuint shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &shaderSourceStr, nullptr);
	glCompileShader(shader);

	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (!status)
	{
		GLint infoLogLen;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLen);
		GLchar *infoLog = new GLchar[infoLogLen + 1];
		throw std::exception(infoLog);

		delete infoLog;
	}

	return shader;
}

GLuint Graphics::InitializeProgram(std::unordered_map<std::string, GLenum> shaderSourcesList)
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
		GLchar *infoLog = new GLchar[infoLogLen + 1];
		throw std::exception(infoLog);

		delete infoLog;
	}

	return program;
}

void Graphics::SetUniforms(GLuint program, float time_uniform, int window_width, int window_height)
{
	GLuint time_uniform_location = glGetUniformLocation(program, "time");
	glUniform1f(time_uniform_location, time_uniform);
	GLuint resolution_uniform_location = glGetUniformLocation(program, "resolution");
	glUniform2i(resolution_uniform_location, window_width, window_height);
}

void Graphics::Reshape(GLint xpos, GLint ypos, GLsizei width, GLsizei height)
{
	glViewport(xpos, ypos, width, height);
}
