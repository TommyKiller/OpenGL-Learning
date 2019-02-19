#include "InputController.h"

Input::InputController* Input::InputController::instance = nullptr;

Input::InputController::InputController()
{}

Input::InputController* Input::InputController::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new Input::InputController();
	}

	return instance;
}

void Input::InputController::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key != GLFW_KEY_UNKNOWN)
	{
		Input::InputController* ic = Input::InputController::GetInstance();
		switch (action)
		{
		case GLFW_PRESS:
		{
			ic->SetKeyState(key, true);
			break;
		}
		case GLFW_RELEASE:
		{
			ic->SetKeyState(key, false);
			break;
		}
		}
	}
}

void Input::InputController::SetKeyState(int key, bool state)
{
	keys[key] = state;
}

bool Input::InputController::KeyPressed(int key)
{
	if (!keys.count(key))
	{
		return false;
	}
	else
	{
		return keys[key];
	}
}

Input::InputController::~InputController()
{
	delete instance;
}
