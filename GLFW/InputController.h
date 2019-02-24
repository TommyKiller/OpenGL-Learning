#ifndef INPUTCONTROLLER_H
#define INPUTCONTROLLER_H
#include <GLFW/glfw3.h>
#include <unordered_map>
#include <algorithm>
#include <memory>
#include "Event.h"


namespace Input
{
	// Actions //
	constexpr auto ACTION_MOVE_FORWARD = 0;
	constexpr auto ACTION_MOVE_BACKWARD = 1;
	constexpr auto ACTION_MOVE_LEFT = 2;
	constexpr auto ACTION_MOVE_RIGHT = 3;
	constexpr auto ACTION_EXIT = 4;
	constexpr auto ACTION_SWITCH_SCREEN_MODE = 5;
	// Events //
	constexpr auto EVENT_MOVE = 0;
	constexpr auto EVENT_EXIT = 1;
	constexpr auto EVENT_SWITCH_SCREEN_MODE = 2;

	class InputController
	{
	public:
		static InputController& GetInstance();

		static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

		void PollEvents();

		void SubscribeTo(int event, Events::Delegate* delegate);

		void UnsubscribeTo(int event, Events::Delegate* delegate);

		int GetKey(int action);

		int GetKeyMods(int key);

		bool KeyModded(int key);

		bool KeyPressed(int key);

		bool KeyHandled(int key);

	private:
		struct Key
		{
			int scancode;
			int mods;
			bool modded;
			bool pressed;
			bool handled;
		};

		std::unordered_map<int, Key> keys;

		std::vector<Events::Event*> events
		{
			new Events::Event(),
			new Events::Event(),
			new Events::Event()
		};

		std::unordered_map<int, int> actions
		{
			{ACTION_MOVE_FORWARD, GLFW_KEY_W},
			{ACTION_MOVE_BACKWARD, GLFW_KEY_S},
			{ACTION_MOVE_LEFT, GLFW_KEY_A},
			{ACTION_MOVE_RIGHT, GLFW_KEY_D},
			{ACTION_EXIT, GLFW_KEY_ESCAPE},
			{ACTION_SWITCH_SCREEN_MODE, GLFW_KEY_F11}
		};

		void PollEvent(int event);

		void AddKey(int key, int scancode);

		void SetKeyDefalut(int key);

		void SetKeyPressed(int key, bool pressed);

		void SetKeyHandled(int key, bool handled);

		void SetKeyMods(int key, int mods);

		bool HasKey(int key);

		InputController();

		InputController(InputController&) = delete;

		InputController& operator=(const InputController&) = delete;

		~InputController();
	};
}


#endif
