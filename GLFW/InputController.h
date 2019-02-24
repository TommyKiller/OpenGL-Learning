#ifndef INPUTCONTROLLER_H
#define INPUTCONTROLLER_H
#include <GLFW/glfw3.h>
#include <unordered_map>
#include <algorithm>
#include <memory>
#include "Event.h"
/* Actions */
#define ACTION_MOVE_FORWARD 0
#define ACTION_MOVE_BACKWARD 1
#define ACTION_MOVE_LEFT 2
#define ACTION_MOVE_RIGHT 3
#define ACTION_EXIT 4
#define ACTION_SWITCH_SCREEN_MODE 5
/* Events */
#define EVENT_MOVE 0
#define EVENT_EXIT 1
#define EVENT_SWITCH_SCREEN_MODE 2

namespace Input
{
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

		std::unordered_map<int, Events::Event*> events
		{
			{EVENT_MOVE, new Events::Event()},
			{EVENT_EXIT, new Events::Event()},
			{EVENT_SWITCH_SCREEN_MODE, new Events::Event()}
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
