#include "Engine.h"
#include "Editor.h"

int main()
{
	System::Engine::Initialize(4, 6, 0, 0, 1360, 768, "Test", true);
	Input::Initialize<Input::FPSInputActions>(Input::FPSLayout);
	// FOR TEST //
	System::CreateTest();
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	// END FOR TEST //
	while (!System::Window::GetInstance().ShouldClose())
	{
		glfwPollEvents();
		Input::InputController::GetInstance().PollEvents();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		Graphics::Scene::GetInstance().Render();

		System::Window::GetInstance().SwapBuffers();
	}

	return 0;
}