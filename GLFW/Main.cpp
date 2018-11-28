#include <cmath>
#include "framework.h"


//int Tapper(int x, long double y) // 0 <= x <= 106
//{
//	return 0.5 < floorl(fmodl(floorl(y / 17.0f) * powl(2, (-17 * floorl(x) - fmodl(floorl(y), 17.0))), 2)) ? 1 : 0;
//}


std::vector<float> vertecies =
{
	 0.75f,  0.75f, 0.0f, 1.0f,
	 0.75f, -0.75f, 0.0f, 1.0f,
	-0.75f, -0.75f, 0.0f, 1.0f
};


std::unordered_map<std::string, GLenum> shaderFiles = 
{
	{ "Shaders/vertexShader.shr", GL_VERTEX_SHADER },
	{ "Shaders/fragmentShader.shr", GL_FRAGMENT_SHADER }
};


int main()
{
	GLFWwindow *window = Graphics::InitializeWindow(1360, 768, "Test");
	GLuint vertex_buffer = Graphics::InitializeBuffer(GL_ARRAY_BUFFER, vertecies, GL_STATIC_DRAW);
	GLuint program = Graphics::InitializeProgram(shaderFiles);
	GLuint vertex_array = Graphics::InitializeVertexArray();
	Graphics::WriteToVAO(vertex_array, vertex_buffer, GL_ARRAY_BUFFER, 0, 4, GL_FLOAT, GL_FALSE, 0, 0);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glClearColor(0.2f, 0.3f, 0.3f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(program);
		glBindVertexArray(vertex_array);
		glEnableVertexAttribArray(0);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		glDisableVertexAttribArray(0);
		glBindVertexArray(0);
		glUseProgram(0);

		glfwSwapBuffers(window);
	}

	glfwTerminate();

	return 0;
}