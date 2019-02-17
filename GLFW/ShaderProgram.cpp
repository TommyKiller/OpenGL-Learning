#include "ShaderProgram.h"

Graphics::ShaderProgram::ShaderProgram(ShaderProgram& shader)
{
	ID = shader.ID;
}

Graphics::ShaderProgram::ShaderProgram(std::unordered_map<std::string, GLenum> shaderSourcesList)
{
	ID = InitialiseProgram(shaderSourcesList);
}

void Graphics::ShaderProgram::bind()
{
	glUseProgram(ID);
}

GLuint Graphics::ShaderProgram::GetAttribLocation(std::string attribute_name)
{
	return glGetAttribLocation(ID, attribute_name.c_str());
}

void Graphics::ShaderProgram::SetUniform(std::string uniform_name, float uniform_value)
{
	GLuint uniform_location = glGetUniformLocation(ID, uniform_name.c_str());
	glUniform1f(uniform_location, uniform_value);
}

void Graphics::ShaderProgram::SetUniform(std::string uniform_name, int uniform_value1, int uniform_value2)
{
	GLuint uniform_location = glGetUniformLocation(ID, uniform_name.c_str());
	glUniform2i(uniform_location, uniform_value1, uniform_value2);
}

void Graphics::ShaderProgram::SetUniform(std::string uniform_name, int count, GLboolean transpose, glm::mat4 uniform_value)
{
	GLuint uniform_location = glGetUniformLocation(ID, uniform_name.c_str());
	glUniformMatrix4fv(uniform_location, count, transpose, glm::value_ptr(uniform_value));
}

void Graphics::ShaderProgram::unbind()
{
	glUseProgram(0);
}

GLuint Graphics::ShaderProgram::CreateShader(GLenum shaderType, std::string fileName)
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

GLuint Graphics::ShaderProgram::InitialiseProgram(std::unordered_map<std::string, GLenum> shaderSourcesList)
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

GLuint Graphics::ShaderProgram::CreateProgram(std::vector<GLuint> shaderList)
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
