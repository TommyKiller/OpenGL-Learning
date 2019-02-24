#ifndef INPUTCONTROLLER_H
#define INPUTCONTROLLER_H
#include <GLFW/glfw3.h>
#include <unordered_map>
#include <algorithm>
#include <memory>
#include "Event.h"

namespace Input
{
	enum Action
	{
		ACTION_MOVE_FORWARD,
		ACTION_MOVE_BACKWARD,
		ACTION_MOVE_LEFT,
		ACTION_MOVE_RIGHT,
		ACTION_SWITCH_SCREEN_MODE,
		ACTION_EXIT
	};

	enum Event
	{
		EVENT_MOVE,
		EVENT_EXIT,
		EVENT_SWITCH_SCREEN_MODE
	};


	class InputController
	{
	public:
		static InputController& GetInstance();

		static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

		void PollEvents();

		void SubscribeTo(Event event, Events::Delegate* delegate);

		void UnsubscribeTo(Event event, Events::Delegate* delegate);

		int GetKey(Action action);

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

		std::unordered_map<Event, Events::Event*> events
		{
			{Event::EVENT_MOVE, new Events::Event()},
			{Event::EVENT_EXIT, new Events::Event()},
			{Event::EVENT_SWITCH_SCREEN_MODE, new Events::Event()}
		};

		std::unordered_map<Action, int> actions
		{
			{Action::ACTION_MOVE_FORWARD, GLFW_KEY_W},
			{Action::ACTION_MOVE_BACKWARD, GLFW_KEY_S},
			{Action::ACTION_MOVE_LEFT, GLFW_KEY_A},
			{Action::ACTION_MOVE_RIGHT, GLFW_KEY_D},
			{Action::ACTION_EXIT, GLFW_KEY_ESCAPE},
			{Action::ACTION_SWITCH_SCREEN_MODE, GLFW_KEY_F11}
		};

		void PollEvent(Event event);

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
