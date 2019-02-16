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
	if (key == GLFW_KEY_W && action == GLFW_PRESS)
	{

	}
	if (key == GLFW_KEY_S && action == GLFW_PRESS)
	{

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

void Graphics::ReshapeViewport(GLint xpos, GLint ypos, GLsizei width, GLsizei height)
{
	glViewport(xpos, ypos, width, height);
}

Graphics::Shader::Shader(Shader& shader)
{
	ID = shader.ID;
}

Graphics::Shader::Shader(std::unordered_map<std::string, GLenum> shaderSourcesList)
{
	ID = InitialiseProgram(shaderSourcesList);
}

void Graphics::Shader::bind()
{
	glUseProgram(ID);
}

GLuint Graphics::Shader::GetAttribLocation(std::string attribute_name)
{
	return glGetAttribLocation(ID, attribute_name.c_str());
}

void Graphics::Shader::SetUniform(std::string uniform_name, float uniform_value)
{
	GLuint uniform_location = glGetUniformLocation(ID, uniform_name.c_str());
	glUniform1f(uniform_location, uniform_value);
}

void Graphics::Shader::SetUniform(std::string uniform_name, int uniform_value1, int uniform_value2)
{
	GLuint uniform_location = glGetUniformLocation(ID, uniform_name.c_str());
	glUniform2i(uniform_location, uniform_value1, uniform_value2);
}

void Graphics::Shader::SetUniform(std::string uniform_name, int count, GLboolean transpose, glm::mat4 uniform_value)
{
	GLuint uniform_location = glGetUniformLocation(ID, uniform_name.c_str());
	glUniformMatrix4fv(uniform_location, count, transpose, glm::value_ptr(uniform_value));
}

void Graphics::Shader::unbind()
{
	glUseProgram(0);
}

GLuint Graphics::Shader::CreateShader(GLenum shaderType, std::string fileName)
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

GLuint Graphics::Shader::InitialiseProgram(std::unordered_map<std::string, GLenum> shaderSourcesList)
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

GLuint Graphics::Shader::CreateProgram(std::vector<GLuint> shaderList)
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
