#include <cmath>
#include "framework.h"

//int Tapper(int x, long double y) // 0 <= x <= 106
//{
//	return 0.5 < floorl(fmodl(floorl(y / 17.0f) * powl(2, (-17*  floorl(x) - fmodl(floorl(y), 17.0))), 2)) ? 1 : 0;
//}


std::vector<GLfloat>* v1 = new std::vector<GLfloat>
{
	 1.0f, -1.0f, -1.0f, 1.0f,
	-1.0f, -1.0f, -1.0f, 1.0f,
	-1.0f, -1.0f,  1.0f, 1.0f,
	 1.0f, -1.0f,  1.0f, 1.0f,
	 0.0f,  1.0f,  0.0f, 1.0f,
};


std::vector<GLfloat>* vc1 = new std::vector<GLfloat>
{
	1.0f, 0.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 1.0f, 1.0f
};


std::vector<GLuint>* el1 = new std::vector<GLuint>
{
	0, 4, 1,
	1, 4, 2,
	2, 4, 3,
	3, 4, 0,
	0, 1, 2,
	0, 2, 3
};

unsigned int vertex_coords_count = 20;
GLfloat* vertex_coords = new GLfloat[vertex_coords_count]
{
	 1.0f, -1.0f, -1.0f, 1.0f,
	-1.0f, -1.0f, -1.0f, 1.0f,
	-1.0f, -1.0f,  1.0f, 1.0f,
	 1.0f, -1.0f,  1.0f, 1.0f,
	 0.0f,  1.0f,  0.0f, 1.0f,
};

unsigned int vertex_colours_count = 20;
GLfloat* vertex_colours = new GLfloat[vertex_colours_count]
{
	1.0f, 0.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 1.0f, 1.0f
};

unsigned int elements_count = 18;
GLuint* elements = new GLuint[elements_count]
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
	GLFWwindow* window = Graphics::InitialiseWindow(0, 0, 1360, 768, false, "Test");
	System::InitialiseGLEW(window);
	// Set callbacks //
	glfwSetFramebufferSizeCallback(window, Callbacks::FramebufferSizeCallback);
	glfwSetKeyCallback(window, Callbacks::KeyCallback);


	Graphics::Shader shader(shaderFiles);
	Graphics::Mesh* pyramid_mesh = new Graphics::Mesh(vertex_coords, vertex_coords_count, vertex_colours, vertex_colours_count, elements, elements_count, GL_STATIC_DRAW);

	glEnable(GL_DEPTH_TEST);
	glfwSetTime(0);

	int framebuffer_width, framebuffer_height;
	glfwGetFramebufferSize(window, &framebuffer_width, &framebuffer_height);
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)framebuffer_width / (GLfloat)framebuffer_height, 0.1f, 100.0f);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glClearColor(0.2f, 0.3f, 0.3f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		////
		glm::mat4 model(1);
		model = glm::translate(model, triangle_location);
		model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		////
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