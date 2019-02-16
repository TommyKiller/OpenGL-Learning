#include <cmath>
#include "framework.h"

//int Tapper(int x, long double y) // 0 <= x <= 106
//{
//	return 0.5 < floorl(fmodl(floorl(y / 17.0f) * powl(2, (-17*  floorl(x) - fmodl(floorl(y), 17.0))), 2)) ? 1 : 0;
//}


std::vector<float>* vertecies = new std::vector<float>
{
	// Coordinates //
	 1.0f, -1.0f, -1.0f, 1.0f,
	-1.0f, -1.0f, -1.0f, 1.0f,
	-1.0f, -1.0f,  1.0f, 1.0f,
	 1.0f, -1.0f,  1.0f, 1.0f,
	 0.0f,  1.0f,  0.0f, 1.0f,
	// Colors //
	1.0f, 0.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 1.0f, 1.0f
};


std::vector<unsigned int>* elements = new std::vector<unsigned int>
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
	GLFWwindow* window = Graphics::InitialiseWindow(0, 0, 1360, 768, true, "Test");
	System::InitialiseGLEW(window);
	// Set callbacks //
	glfwSetFramebufferSizeCallback(window, Callbacks::FramebufferSizeCallback);
	glfwSetKeyCallback(window, Callbacks::KeyCallback);

	GLuint vertex_buffer = Graphics::InitialiseBuffer(GL_ARRAY_BUFFER, vertecies, GL_STATIC_DRAW);
	GLuint elements_buffer = Graphics::InitialiseBuffer(GL_ELEMENT_ARRAY_BUFFER, elements, GL_STATIC_DRAW);
	Graphics::Shader shader(shaderFiles);
	GLuint vertex_array = Graphics::InitializeVertexArray();
	GLint position_location = shader.GetAttribLocation("position");
	GLint color_location = shader.GetAttribLocation("color");
	Graphics::WriteToVAO(vertex_array, vertex_buffer, GL_ARRAY_BUFFER, position_location, 4, GL_FLOAT, GL_FALSE, 0, 0);
	Graphics::WriteToVAO(vertex_array, vertex_buffer, GL_ARRAY_BUFFER, color_location, 4, GL_FLOAT, GL_FALSE, 0, (const void*)80);

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

		shader.SetUniform("time", (GLfloat)glfwGetTime());
		shader.SetUniform("framebuffer_size", framebuffer_width, framebuffer_height);
		shader.SetUniform("model", 1, GL_FALSE, model);
		shader.SetUniform("projection", 1, GL_FALSE, projection);

		glBindVertexArray(vertex_array);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elements_buffer);
		glEnableVertexAttribArray(position_location);
		glEnableVertexAttribArray(color_location);

		glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);

		glDisableVertexAttribArray(color_location);
		glDisableVertexAttribArray(position_location);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		shader.unbind();

		glfwSwapBuffers(window);
	}

	glfwTerminate();

	return 0;
}