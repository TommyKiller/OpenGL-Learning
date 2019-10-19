#ifndef SHADER_H
#define SHADER_H
#include <GL/glew.h>
#include <GLM/glm.hpp>
#include <GLM/gtc/type_ptr.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace Graphics
{
	class Shader
	{
	public:
		Shader() = delete;

		Shader(const char* vertex_shader_file, const char* fragment_shader_file);

		Shader(const char* vertex_shader_file, const char* fragment_shader_file, const char* geometry_shader_file);

		void Bind() const;
		void Unbind() const;
		GLuint GetID() const;

		GLuint GetAttribLocation(const char* attrib_name) const;

		// Setting uniforms
		void SetUniform(const char* uniform_name, const glm::mat4 matrix) const;
		void SetUniform(const char* uniform_name, const int texture_unit) const;

		void Dispose();

		~Shader();

	private:
		GLuint ID;

		GLuint LoadShader(GLenum shader_type, const char* file_path);

		void LinkProgram(std::vector<GLuint> shaders);
	};
}

#endif
