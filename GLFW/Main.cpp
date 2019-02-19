#include <cmath>
#include <vector>
#include "framework.h"

//int Tapper(int x, long double y) // 0 <= x <= 106
//{
//	return 0.5 < floorl(fmodl(floorl(y / 17.0f) * powl(2, (-17*  floorl(x) - fmodl(floorl(y), 17.0))), 2)) ? 1 : 0;
//}


const float MOVING_SPEED = 0.02f;


Graphics::Window* window;
Graphics::Mesh* pyramid_mesh;
Graphics::ShaderProgram* shader;
glm::vec3 triangle_translation(0.0f, 0.0f, -2.0f);
glm::mat4 projection;
glm::mat4 model;


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


std::unordered_map<GLenum, const char*> shaderFiles =
{
	{ GL_VERTEX_SHADER, "Shaders/vertexShader.shr" },
	{ GL_FRAGMENT_SHADER, "Shaders/fragmentShader.shr" }
};

void HandleInput()
{
	Input::InputController* ic = Input::InputController::GetInstance();
	if (ic->KeyPressed(GLFW_KEY_ESCAPE))
	{
		window->Close();
	}
	if (ic->KeyPressed(GLFW_KEY_F11))
	{
		if (window->IsFullscreen())
		{
			window->Windowed();
		}
		else
		{
			window->Fullscreen();
		}
	}
	if (ic->KeyPressed(GLFW_KEY_W))
	{
		triangle_translation.z += MOVING_SPEED;
	}
	if (ic->KeyPressed(GLFW_KEY_S))
	{
		triangle_translation.z -= MOVING_SPEED;
	}
	if (ic->KeyPressed(GLFW_KEY_A))
	{
		triangle_translation.x += MOVING_SPEED;
	}
	if (ic->KeyPressed(GLFW_KEY_D))
	{
		triangle_translation.x -= MOVING_SPEED;
	}
	if (ic->KeyPressed(GLFW_KEY_LEFT_CONTROL))
	{
		triangle_translation.y += MOVING_SPEED;
	}
	if (ic->KeyPressed(GLFW_KEY_SPACE))
	{
		triangle_translation.y -= MOVING_SPEED;
	}
}

int main()
{
	System::InitialiseGLFW();
	window = new Graphics::Window(0, 0, 1360, 768, "Test", true);
	window->MakeCurrent();
	window->SetCallbacks(Callbacks::FramebufferSizeCallback, Input::InputController::KeyCallback);
	System::InitialiseGLEW(window);
	System::SetUpGLSettings(glm::vec4(0.4f, 0.4f, 0.4f, 0.0f));

	// Create objects //
	shader = new Graphics::ShaderProgram(shaderFiles);
	pyramid_mesh = new Graphics::Mesh(pyramid_vertex_data->data(), pyramid_vertex_data->size(), elements->data(), elements->size(), GL_STATIC_DRAW);

	// Projection matrix //
	int framebuffer_width, framebuffer_height;
	window->GetFramebufferSize(&framebuffer_width, &framebuffer_height);
	projection = glm::perspective(45.0f, (GLfloat)framebuffer_width / (GLfloat)framebuffer_height, 0.1f, 100.0f);

	while (!window->ShouldClose())
	{
		glfwPollEvents();
		HandleInput();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Model matrix //
		model = glm::translate(glm::mat4(1), triangle_translation);
		model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));

		// Rendering //
		shader->bind();
		shader->SetUniform("model", 1, GL_FALSE, model);
		shader->SetUniform("projection", 1, GL_FALSE, projection);

		pyramid_mesh->Render();

		shader->unbind();

		window->SwapBuffers();
	}

	glfwTerminate();

	return 0;
}
