#include "InputController.h"

Input::InputController::InputController()
{}

Input::InputController& Input::InputController::GetInstance()
{
	static Input::InputController instance;

	return instance;
}

void Input::InputController::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key != GLFW_KEY_UNKNOWN)
	{
		switch (action)
		{
		case GLFW_PRESS:
		{
			Input::InputController::GetInstance().SetKeyPressedState(key, true);
			if (Input::InputController::GetInstance().IsHandled(key) == -1)
			{
				Input::InputController::GetInstance().SetKeyHandledState(key, false);
			}
			break;
		}
		case GLFW_RELEASE:
		{
			Input::InputController::GetInstance().SetKeyPressedState(key, false);
			Input::InputController::GetInstance().SetKeyHandledState(key, false);
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
{}
