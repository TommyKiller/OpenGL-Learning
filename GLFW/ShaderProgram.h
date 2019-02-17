#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <GL/glew.h>
#include <GLM/gtc/type_ptr.hpp>
#include <string>
#include <unordered_map>
#include <fstream>
#include <algorithm>

namespace Graphics
{
	class ShaderProgram
	{
	public:
		ShaderProgram() = delete;

		ShaderProgram(ShaderProgram& shaderProgram);

		ShaderProgram(std::unordered_map<std::string, GLenum> shaderSourcesList);

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
