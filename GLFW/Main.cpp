#include <cmath>
#include <vector>
#include "framework.h"

//int Tapper(int x, long double y) // 0 <= x <= 106
//{
//	return 0.5 < floorl(fmodl(floorl(y / 17.0f) * powl(2, (-17*  floorl(x) - fmodl(floorl(y), 17.0))), 2)) ? 1 : 0;
//}


const float MOVING_SPEED = 0.02f;


System::Window* window;
Engine::Scene* scene;
Graphics::Object* pyramid;
Graphics::ShaderProgram* shader;


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
	if (Engine::InputController::GetInstance().KeyPressed(GLFW_KEY_ESCAPE))
	{
		window->Close();
	}
	if (Engine::InputController::GetInstance().KeyPressed(GLFW_KEY_F11) &&
		!Engine::InputController::GetInstance().KeyHandled(GLFW_KEY_F11))
	{
		if (window->IsFullscreen())
		{
			window->Windowed();
		}
		else
		{
			window->Fullscreen();
		}
		Engine::InputController::GetInstance().SetKeyHandled(GLFW_KEY_F11, true);
	}
	if (Engine::InputController::GetInstance().KeyPressed(GLFW_KEY_W))
	{
		pyramid->Move(0.0f, 0.0f, MOVING_SPEED);
	}
	if (Engine::InputController::GetInstance().KeyPressed(GLFW_KEY_S))
	{
		pyramid->Move(0.0f, 0.0f, -MOVING_SPEED);
	}
	if (Engine::InputController::GetInstance().KeyPressed(GLFW_KEY_A))
	{
		pyramid->Move(MOVING_SPEED, 0.0f, 0.0f);
	}
	if (Engine::InputController::GetInstance().KeyPressed(GLFW_KEY_D))
	{
		pyramid->Move(-MOVING_SPEED, 0.0f, 0.0f);
	}
	if (Engine::InputController::GetInstance().KeyPressed(GLFW_KEY_LEFT_CONTROL))
	{
		pyramid->Move(0.0f, MOVING_SPEED, 0.0f);
	}
	if (Engine::InputController::GetInstance().KeyPressed(GLFW_KEY_SPACE))
	{
		pyramid->Move(0.0f, -MOVING_SPEED, 0.0f);
	}
}

int main()
{
	// Setting system up //
	System::InitialiseGLFW();
	window = new System::Window(0, 0, 1360, 768, "Test", true);
	window->MakeCurrent();
	window->SetCallbacks(Graphics::Render::GetInstance().FramebufferSizeCallback, Engine::InputController::KeyCallback);
	System::InitialiseGLEW(window);
	Graphics::Render::GetInstance().ClearColor(glm::vec4(0.4f, 0.3f, 0.5f, 1.0f));
	Graphics::Render::GetInstance().Enable(GL_DEPTH_TEST);

	// Create objects //
	int framebuffer_width, framebuffer_height;
	window->GetFramebufferSize(&framebuffer_width, &framebuffer_height);
	scene = new Engine::Scene(glm::perspective(45.0f, (GLfloat)framebuffer_width / (GLfloat)framebuffer_height, 0.1f, 100.0f));
	pyramid = new Graphics::Object(std::make_shared<Graphics::Mesh>(pyramid_vertex_data->data(), pyramid_vertex_data->size(), elements->data(), elements->size(), GL_STATIC_DRAW),
		glm::vec3(0.0f, 0.0f, -2.0f), glm::vec3(0.5f, 0.5f, 0.5f));
	scene->AddObject(pyramid);
	shader = new Graphics::ShaderProgram(shaderFiles);

	while (!window->ShouldClose())
	{
		glfwPollEvents();
		HandleInput();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// ... //
		pyramid->Rotate((float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));

		// Rendering //
		Graphics::Render::GetInstance()(shader, scene);

		window->SwapBuffers();
	}

	glfwTerminate();

	return 0;
}
