#include <cmath>
#include "framework.h"

//int Tapper(int x, long double y) // 0 <= x <= 106
//{
//	return 0.5 < floorl(fmodl(floorl(y / 17.0f) * powl(2, (-17*  floorl(x) - fmodl(floorl(y), 17.0))), 2)) ? 1 : 0;
//}


std::vector<float>* vertecies = new std::vector<float>
{
	// Coordinates //
	// First trianlge //
	 0.0f,  0.5f,   0.0f, 1.0f,
	 0.5f, -0.366f, 0.0f, 1.0f,
	-0.5f, -0.366f, 0.0f, 1.0f,
	// Second trianlge //
	-0.75f, -0.75f, 1.0f, 1.0f,
	-0.75f,  0.75f, 1.0f, 1.0f,
	 0.75f,  0.75f, 1.0f, 1.0f,

	// Colors //
	// First trianlge //
	1.0f, 0.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f, 1.0f,
	// Second trianlge //
	0.0f, 0.0f, 1.0f, 1.0f,
	0.0f, 1.0f, 0.0f, 1.0f,
	1.0f, 0.0f, 0.0f, 1.0f
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

	GLuint vertex_buffer = Graphics::InitialiseBuffer(GL_ARRAY_BUFFER, vertecies, GL_STREAM_DRAW);
	Graphics::Shader shader(shaderFiles);
	GLuint vertex_array = Graphics::InitializeVertexArray();
	GLint position_location = shader.GetAttribLocation("position");
	GLint color_location = shader.GetAttribLocation("color");
	Graphics::WriteToVAO(vertex_array, vertex_buffer, GL_ARRAY_BUFFER, position_location, 4, GL_FLOAT, GL_FALSE, 0, 0);
	Graphics::WriteToVAO(vertex_array, vertex_buffer, GL_ARRAY_BUFFER, color_location, 4, GL_FLOAT, GL_FALSE, 0, (const void* )96);

	glfwSetTime(0);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glClearColor(0.2f, 0.3f, 0.3f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader.bind();

		glm::mat4 model = glm::translate(glm::mat4(), glm::vec3(0.1f, 0.0f, 0.0f));
		//model = glm::rotate(model, glm::degrees(1.0f), glm::vec3(0.0f, 1.0f, 0.0f));

		int framebuffer_width, framebuffer_height;
		glfwGetFramebufferSize(window, &framebuffer_width, &framebuffer_height);
		shader.SetUniform("time", (GLfloat)glfwGetTime());
		shader.SetUniform("framebuffer_size", framebuffer_width, framebuffer_height);
		shader.SetUniform("model", 1, GL_FALSE, model);

		glBindVertexArray(vertex_array);
		glEnableVertexAttribArray(position_location);
		glEnableVertexAttribArray(color_location);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		glEnableVertexAttribArray(color_location);
		glDisableVertexAttribArray(position_location);
		glBindVertexArray(0);
		shader.unbind();

		glfwSwapBuffers(window);
	}

	glfwTerminate();

	return 0;
}