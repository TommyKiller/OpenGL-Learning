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
			if (!Input::InputController::GetInstance().HasKey(key))
			{
				Input::InputController::GetInstance().AddKey(key, scancode);
			}
			if (!Input::InputController::GetInstance().KeyPressed(key))
			{
				Input::InputController::GetInstance().SetKeyPressed(key, true);
				Input::InputController::GetInstance().SetKeyHandled(key, false);
			}
			break;
		}
		case GLFW_RELEASE:
		{
			Input::InputController::GetInstance().SetKeyDefalut(key);
			break;
		}
		}
	}
}

void Input::InputController::PollEvents()
{
	if (KeyPressed(GetKey(ACTION_MOVE_FORWARD)) || KeyPressed(GetKey(ACTION_MOVE_LEFT)) ||
		KeyPressed(GetKey(ACTION_MOVE_BACKWARD)) || KeyPressed(GetKey(ACTION_MOVE_RIGHT)))
	{
		PollEvent(EVENT_MOVE);
	}
	if (KeyPressed(GetKey(ACTION_EXIT)) && !KeyHandled(GetKey(ACTION_EXIT)))
	{
		PollEvent(EVENT_EXIT);
		SetKeyHandled(GetKey(ACTION_EXIT), true);
	}
	if (KeyPressed(GetKey(ACTION_SWITCH_SCREEN_MODE)) && !KeyHandled(GetKey(ACTION_SWITCH_SCREEN_MODE)))
	{
		PollEvent(EVENT_SWITCH_SCREEN_MODE);
		SetKeyHandled(GetKey(ACTION_SWITCH_SCREEN_MODE), true);
	}
}

void Input::InputController::SubscribeTo(Input::Event event, Events::Delegate* delegate)
{
	*events[event] += *delegate;
}

void Input::InputController::UnsubscribeTo(Input::Event event, Events::Delegate* delegate)
{
	*events[event] -= *delegate;
}

int Input::InputController::GetKey(Input::Action action)
{
	return actions[action];
}

void Input::InputController::PollEvent(Input::Event event)
{
	(*events[event])();
}

void Input::InputController::AddKey(int key, int scancode)
{
	keys[key].scancode = scancode;
	SetKeyDefalut(key);
}

void Input::InputController::SetKeyDefalut(int key)
{
	keys[key].pressed = false;
	keys[key].handled = true;
	keys[key].modded = false;
}

void Input::InputController::SetKeyPressed(int key, bool pressed)
{
	keys[key].pressed = pressed;
}

void Input::InputController::SetKeyHandled(int key, bool handled)
{
	keys[key].handled = handled;
}

void Input::InputController::SetKeyMods(int key, int mods)
{
	keys[key].mods = mods;
	keys[key].modded = true;
}

int Input::InputController::GetKeyMods(int key)
{
	return keys[key].mods;
}

bool Input::InputController::HasKey(int key)
{
	return keys.count(key);
}

bool Input::InputController::KeyPressed(int key)
{
	return keys[key].pressed;
}

bool Input::InputController::KeyHandled(int key)
{
	return keys[key].handled;
}

bool Input::InputController::KeyModded(int key)
{
	return keys[key].mods;
}

Input::InputController::~InputController()
{}
