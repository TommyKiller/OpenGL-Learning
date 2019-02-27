#include <cmath>
#include <vector>
#include "framework.h"

//int Tapper(int x, long double y) // 0 <= x <= 106
//{
//	return 0.5 < floorl(fmodl(floorl(y / 17.0f) * powl(2, (-17*  floorl(x) - fmodl(floorl(y), 17.0))), 2)) ? 1 : 0;
//}


const float MOVING_SPEED = 0.02f;


System::Window* window;
Graphics::Scene* scene;
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

int main()
{
	// Setting system up //
	System::InitialiseGLFW(3, 3);
	window = new System::Window(0, 0, 1360, 768, "Test", true);
	window->MakeCurrent();
	window->SetCallbacks(Graphics::Render::GetInstance().FramebufferSizeCallback, Input::InputController::KeyCallback, Input::InputController::MouseCallback);
	window->DisableCursor();
	System::InitialiseGLEW(window);
	Graphics::Render::GetInstance().ClearColor(glm::vec4(0.4f, 0.3f, 0.5f, 1.0f));
	Graphics::Render::GetInstance().Enable(GL_DEPTH_TEST);

	// Create objects //
	int framebuffer_width, framebuffer_height;
	window->GetFramebufferSize(&framebuffer_width, &framebuffer_height);
	scene = new Graphics::Scene(glm::perspective(45.0f, (GLfloat)framebuffer_width / (GLfloat)framebuffer_height, 0.1f, 100.0f));
	pyramid = new Graphics::Object(std::make_shared<Graphics::Mesh>(pyramid_vertex_data->data(), pyramid_vertex_data->size(), elements->data(), elements->size(), GL_STATIC_DRAW),
		glm::vec3(0.0f, 0.0f, -2.0f), glm::vec3(0.5f, 0.5f, 0.5f));
	scene->AddObject(pyramid);
	shader = new Graphics::ShaderProgram(shaderFiles);
	Graphics::Camera::GetInstance().Initialise(glm::vec3(0.0f, 0.0f, -3.0f), glm::vec3(0.0f, 1.0f, 0.0f), 90.0f, 0.0f, 3.0f, 0.1f);

	while (!window->ShouldClose())
	{
		System::CalcDeltaTime();

		glfwPollEvents();
		Input::InputController::GetInstance().PollEvents();

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
