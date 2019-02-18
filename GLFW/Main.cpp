#include <cmath>
#include <vector>
#include "framework.h"

//int Tapper(int x, long double y) // 0 <= x <= 106
//{
//	return 0.5 < floorl(fmodl(floorl(y / 17.0f) * powl(2, (-17*  floorl(x) - fmodl(floorl(y), 17.0))), 2)) ? 1 : 0;
//}


std::vector<GLfloat>* vertex_coords = new std::vector<GLfloat>
{
	 1.0f, -1.0f, -1.0f, 1.0f,
	-1.0f, -1.0f, -1.0f, 1.0f,
	-1.0f, -1.0f,  1.0f, 1.0f,
	 1.0f, -1.0f,  1.0f, 1.0f,
	 0.0f,  1.0f,  0.0f, 1.0f,
};


std::vector<GLfloat>* vertex_colours = new std::vector<GLfloat>
{
	1.0f, 0.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 1.0f, 1.0f
};

std::vector<std::pair<GLfloat*, unsigned int>>* pyramid_vertex_data = new std::vector<std::pair<GLfloat*, unsigned int>>
{
	std::pair<GLfloat*, unsigned int>(vertex_coords->data(), vertex_coords->size()),
	std::pair<GLfloat*, unsigned int>(vertex_colours->data(), vertex_colours->size())
};

std::vector<GLuint>* elements = new std::vector<GLuint>
{
	0, 4, 1,
	1, 4, 2,
	2, 4, 3,
	3, 4, 0,
	0, 1, 2,
	0, 2, 3
};


std::unordered_map<std::string, GLenum> shaderFiles = 
{
	{ "Shaders/vertexShader.shr", GL_VERTEX_SHADER },
	{ "Shaders/fragmentShader.shr", GL_FRAGMENT_SHADER }
};


int main()
{
	System::InitialiseGLFW();
	GLFWwindow* window = System::InitialiseWindow(0, 0, 1360, 768, false, "Test");
	System::InitialiseGLEW(window);
	System::SetUpGLSettings(glm::vec4(0.4f, 0.4f, 0.4f, 0.0f));

	// Set callbacks //
	glfwSetFramebufferSizeCallback(window, Callbacks::FramebufferSizeCallback);
	glfwSetKeyCallback(window, Callbacks::KeyCallback);

	// Create objects //
	Graphics::ShaderProgram shader(shaderFiles);
	Graphics::Mesh* pyramid_mesh = new Graphics::Mesh(pyramid_vertex_data->data(), pyramid_vertex_data->size(), elements->data(), elements->size(), GL_STATIC_DRAW);

	// Uniforms calculations //
	int framebuffer_width, framebuffer_height;
	glfwGetFramebufferSize(window, &framebuffer_width, &framebuffer_height);
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)framebuffer_width / (GLfloat)framebuffer_height, 0.1f, 100.0f);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Model matrix calculations //
		glm::mat4 model(1);
		model = glm::translate(model, triangle_location);
		model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));

		// Rendering //
		shader.bind();
		shader.SetUniform("model", 1, GL_FALSE, model);
		shader.SetUniform("projection", 1, GL_FALSE, projection);

		pyramid_mesh->Render();

		shader.unbind();

		glfwSwapBuffers(window);
	}

	glfwTerminate();

	return 0;
}