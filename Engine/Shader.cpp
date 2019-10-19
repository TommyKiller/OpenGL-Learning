#include "Shader.h"

Graphics::Shader::Shader(const char* vertex_shader_file, const char* fragment_shader_file)
{
	ID = glCreateProgram();
	std::vector<GLuint> shaders;
	shaders.push_back(LoadShader(GL_VERTEX_SHADER, vertex_shader_file));
	shaders.push_back(LoadShader(GL_FRAGMENT_SHADER, fragment_shader_file));
	LinkProgram(shaders);
}

Graphics::Shader::Shader(const char* vertex_shader_file, const char* fragment_shader_file, const char* geometry_shader_file)
{
	ID = glCreateProgram();
	std::vector<GLuint> shaders;
	shaders.push_back(LoadShader(GL_VERTEX_SHADER, vertex_shader_file));
	shaders.push_back(LoadShader(GL_FRAGMENT_SHADER, fragment_shader_file));
	shaders.push_back(LoadShader(GL_GEOMETRY_SHADER, geometry_shader_file));
	LinkProgram(shaders);
}

void Graphics::Shader::Bind() const
{
	glUseProgram(ID);
}

void Graphics::Shader::Unbind() const
{
	glUseProgram(0);
}

GLuint Graphics::Shader::GetID() const
{
	return ID;
}

GLuint Graphics::Shader::GetAttribLocation(const char* attrib_name) const
{
	return glGetAttribLocation(ID, attrib_name);
}

GLuint Graphics::Shader::LoadShader(GLenum shader_type, const char* file_path)
{
	const char* shader_code;
	std::ifstream shader_file;
	std::stringstream shader_stream;
	shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	shader_file.open(file_path);
	shader_stream << shader_file.rdbuf();
	shader_file.close();
	shader_code = shader_stream.str().c_str();

	GLuint shader = glCreateShader(shader_type);
	glShaderSource(shader, 1, &shader_code, NULL);
	glCompileShader(shader);

	GLint success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		GLchar info_log[1024];
		glGetShaderInfoLog(shader, 1024, NULL, info_log);
		std::string error_msg("Failed to compile a shader: ");
		error_msg += info_log;
		throw std::exception(error_msg.c_str());
	}

	return shader;
}

void Graphics::Shader::LinkProgram(std::vector<GLuint> shaders)
{
	for (auto const& shader : shaders)
	{
		glAttachShader(ID, shader);
	}
	glLinkProgram(ID);

	GLint success;
	glGetProgramiv(ID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		GLchar info_log[1024];
		glGetProgramInfoLog(ID, 1024, NULL, info_log);
		std::string error_msg("Failed to compile a shader: ");
		error_msg += info_log;
		throw std::exception(error_msg.c_str());
	}

	for (auto const& shader : shaders)
	{
		glDeleteShader(shader);
	}
}

void Graphics::Shader::SetUniform(const char* uniform_name, const glm::mat4 matrix) const
{
	GLuint uniform_location = glGetUniformLocation(ID, uniform_name);
	glUniformMatrix4fv(uniform_location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Graphics::Shader::SetUniform(const char* uniform_name, const int texture_unit) const
{
	GLuint uniform_location = glGetUniformLocation(ID, uniform_name);
	glUniform1i(uniform_location, texture_unit);
}

void Graphics::Shader::Dispose()
{
	if (ID != 0)
	{
		glDeleteProgram(ID);
		ID = 0;
	}
}

Graphics::Shader::~Shader()
{
	Dispose();
}
