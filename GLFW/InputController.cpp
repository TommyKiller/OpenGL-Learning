#include "InputController.h"

Engine::InputController::InputController()
{}

Engine::InputController& Engine::InputController::GetInstance()
{
	static Engine::InputController instance;

	return instance;
}

void Engine::InputController::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key != GLFW_KEY_UNKNOWN)
	{
		switch (action)
		{
		case GLFW_PRESS:
		{
			if (!Engine::InputController::GetInstance().HasKey(key))
			{
				Engine::InputController::GetInstance().AddKey(key, scancode);
			}
			if (!Engine::InputController::GetInstance().KeyPressed(key))
			{
				Engine::InputController::GetInstance().SetKeyPressed(key, true);
				Engine::InputController::GetInstance().SetKeyHandled(key, false);
			}
			break;
		}
		case GLFW_RELEASE:
		{
			Engine::InputController::GetInstance().SetKeyDefalut(key);
			break;
		}
		}
	}
}

void Engine::InputController::AddKey(int key, int scancode)
{
	keys[key].scancode = scancode;
	SetKeyDefalut(key);
}

void Engine::InputController::SetKeyDefalut(int key)
{
	keys[key].pressed = false;
	keys[key].handled = true;
	keys[key].modded = false;
}

void Engine::InputController::SetKeyPressed(int key, bool pressed)
{
	keys[key].pressed = pressed;
}

void Engine::InputController::SetKeyHandled(int key, bool handled)
{
	keys[key].handled = handled;
}

void Engine::InputController::SetKeyMods(int key, int mods)
{
	keys[key].mods = mods;
	keys[key].modded = true;
}

int Engine::InputController::GetKeyMods(int key)
{
	return keys[key].mods;
}

bool Engine::InputController::HasKey(int key)
{
	return keys.count(key);
}

bool Engine::InputController::KeyPressed(int key)
{
	return keys[key].pressed;
}

bool Engine::InputController::KeyHandled(int key)
{
	return keys[key].handled;
}

bool Engine::InputController::KeyModded(int key)
{
	return keys[key].mods;
}

Engine::InputController::~InputController()
{}
