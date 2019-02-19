#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <GL/glew.h>
#include <GLM/gtc/type_ptr.hpp>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <algorithm>


namespace Graphics
{
	class ShaderProgram
	{
	public:
		ShaderProgram() = delete;

		ShaderProgram(ShaderProgram& shader_program);

		ShaderProgram(std::map<GLenum, std::string> shader_sources_list);

		void AddShader(GLenum shader_type, std::string file_name);

		void bind();

		GLuint GetAttribLocation(std::string attribute_name);

		void SetUniform(std::string uniform_name, float uniform_value);

		void SetUniform(std::string uniform_name, int uniform_value1, int uniform_value2);

		void SetUniform(std::string uniform_name, int count, GLboolean transpose, glm::mat4 uniform_value);

		void unbind();

		void Dispose();

		~ShaderProgram();

	private:
		GLuint ID;

		std::map<GLenum, std::string> shaders_sources;

		GLuint CreateShader(GLenum shader_type, std::string file_name);

		GLuint CreateProgram(std::vector<GLuint> shader_list);
	};
}


#endif
