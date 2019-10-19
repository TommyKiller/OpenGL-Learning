#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H
#include <GLFW/glfw3.h>
#include <memory>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include "Event.h"
#include "InputControllerEvents.h"
#include "InputEvent.h"
#include "InputEvents.h"
#include "Key.h"

namespace Input
{
	class InputController
	{
	public:
		static InputController& GetInstance();

		// Callbacks
		static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void MouseCallback(GLFWwindow* window, double xpos, double ypos);

		// Events
		void PollEvents();
		void SubscribeTo(InputControllerEvents event, Events::Delegate delegate);
		void UnsubscribeTo(InputControllerEvents event, Events::Delegate delegate);
		// Input events
		InputEvent::Trigger GetEventTrigger(InputEvents id);
		Key GetEventKey(InputEvents id);
		void AddEventToQueue(InputEvents id);

		// Mouse
		double GetMouseXChange();
		double GetMouseYChange();
		void SetMouseNewPos(double xpos, double ypos);

		// Keys
		bool IsKeyAssigned(Key key);
		bool IsKeyPressed(Key key);
		void SetKeyPressed(Key key);
		void SetKeyReleased(Key key);
		InputEvents GetEventID(Key key);

	private:
		struct Mouse
		{
			Mouse()
			{
				glfwGetCursorPos(glfwGetCurrentContext(), &lastXPos, &lastYPos);
			}

			double lastXPos;
			double lastYPos;
			double xChange = 0;
			double yChange = 0;
		};

		std::unordered_map<InputControllerEvents, std::shared_ptr<Events::Event>> ic_events 
		{
			{ InputControllerEvents::INPUT_PROCESSED, std::make_shared<Events::Event>() }
		};

		std::unordered_set<KeyEvent, InputEvent::hash> key_events
		{
			KeyEvent(InputEvents::ON_HOLD_KEY_W, InputEvent::Trigger::ON_HOLD, Key(GLFW_KEY_W, NULL)),
			KeyEvent(InputEvents::ON_HOLD_KEY_S, InputEvent::Trigger::ON_HOLD, Key(GLFW_KEY_W, NULL)),
			KeyEvent(InputEvents::ON_HOLD_KEY_A, InputEvent::Trigger::ON_HOLD, Key(GLFW_KEY_W, NULL)),
			KeyEvent(InputEvents::ON_HOLD_KEY_D, InputEvent::Trigger::ON_HOLD, Key(GLFW_KEY_W, NULL)),
			KeyEvent(InputEvents::ON_HOLD_KEY_SPACE, InputEvent::Trigger::ON_HOLD, Key(GLFW_KEY_W, NULL)),
			KeyEvent(InputEvents::ON_HOLD_KEY_LCTRL, InputEvent::Trigger::ON_HOLD, Key(GLFW_KEY_W, NULL))
		};

		std::unordered_set<MouseEvent, InputEvent::hash> mouse_events
		{
			MouseEvent(InputEvents::ON_MOVE_MOUSE_AXIS_X),
			MouseEvent(InputEvents::ON_MOVE_MOUSE_AXIS_Y)
		};

		std::queue<InputEvents> events_queue;
		std::unordered_map<Key, bool, Key::hash> key_pressed;
		Mouse mouse;

		InputController();
		InputController(InputController&) = delete;
		InputController& operator=(const InputController&) = delete;
	};
}


#endif
