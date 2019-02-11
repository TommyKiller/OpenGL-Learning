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
	GLFWwindow* window = Graphics::InitialiseWindow(0, 0, 1360, 768, true, "Test");
	System::InitialiseGLEW(window);
	// Set callbacks //
	glfwSetFramebufferSizeCallback(window, Callbacks::FramebufferSizeCallback);
	glfwSetKeyCallback(window, Callbacks::KeyCallback);

	GLuint vertex_buffer = Graphics::InitialiseBuffer(GL_ARRAY_BUFFER, vertecies, GL_STREAM_DRAW);
	GLuint program = Graphics::InitialiseProgram(shaderFiles);
	GLuint vertex_array = Graphics::InitializeVertexArray();
	GLint position_location = glGetAttribLocation(program, "position");
	GLint color_location = glGetAttribLocation(program, "color");
	Graphics::WriteToVAO(vertex_array, vertex_buffer, GL_ARRAY_BUFFER, position_location, 4, GL_FLOAT, GL_FALSE, 0, 0);
	Graphics::WriteToVAO(vertex_array, vertex_buffer, GL_ARRAY_BUFFER, color_location, 4, GL_FLOAT, GL_FALSE, 0, (const void* )96);

	glfwSetTime(0);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glClearColor(0.2f, 0.3f, 0.3f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(program);
		int resolution[2];
		glfwGetWindowSize(window, &resolution[0], &resolution[1]);
		Graphics::SetUniforms(program, (GLfloat)glfwGetTime(), resolution);
		glBindVertexArray(vertex_array);
		glEnableVertexAttribArray(position_location);
		glEnableVertexAttribArray(color_location);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		glEnableVertexAttribArray(color_location);
		glDisableVertexAttribArray(position_location);
		glBindVertexArray(0);
		glUseProgram(0);

		glfwSwapBuffers(window);
	}

	glfwTerminate();

	return 0;
}