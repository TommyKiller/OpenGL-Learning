#ifndef RENDERER_H
#define RENDERER_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>
#include <algorithm>
#include "Object.h"
#include "Scene.h"
#include "Camera.h"
#include "ShaderProgram.h"


namespace Graphics
{
	class Render
	{
	public:
		static Render& GetInstance();

		static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);

		void Unbind();

		void ReshapeViewport(int xpos, int ypos, int width, int height);

		void ClearColor(glm::vec4 clear_color);

		void Enable(GLenum cap);

		void operator()(ShaderProgram* shader_program, Object* object, glm::mat4 projection = glm::mat4(1));

		void operator()(ShaderProgram* shader_program, Scene* scene);

	private:
		Render();

		Render(Render&);

		Render& operator=(Render&) = delete;

		~Render();
	};
}


#endif