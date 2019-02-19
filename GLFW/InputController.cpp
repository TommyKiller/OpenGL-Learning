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
			ic->SetKeyPressedState(key, true);
			if (ic->IsHandled(key) == -1)
			{
				ic->SetKeyHandledState(key, false);
			}
			break;
		}
		case GLFW_RELEASE:
		{
			ic->SetKeyPressedState(key, false);
			ic->SetKeyHandledState(key, false);
			break;
		}
		}
	}
}

void Input::InputController::SetKeyPressedState(int key, bool state)
{
	keys_pressed[key] = state;
}

void Input::InputController::SetKeyHandledState(int key, bool state)
{
	keys_handled[key] = state;
}

bool Input::InputController::IsPressed(int key)
{
	if (!keys_pressed.count(key))
	{
		return false;
	}
	else
	{
		return keys_pressed[key];
	}
}

int Input::InputController::IsHandled(int key)
{
	if (!keys_handled.count(key))
	{
		return -1;
	}
	else
	{
		return (int)keys_handled[key];
	}
}

Input::InputController::~InputController()
{
	delete instance;
}
