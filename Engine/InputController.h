#ifndef INPUTCONTROLLER_H
#define INPUTCONTROLLER_H
#include <GLFW/glfw3.h>
#include <memory>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include "utilities/make_unordered_map.h"
#include "utilities/Event.h"
#include "InputControllerEvents.h"
#include "InputEvents.h"

namespace Input
{

	struct Key
	{
		Key(int key, int mod)
			: modifier(mod)
		{
			scancode = glfwGetKeyScancode(key);
		}

		bool operator==(const Key& key) const
		{
			return (scancode == key.scancode && modifier == key.modifier);
		}

		struct hash
		{
			size_t operator()(const Key& key) const
			{
				return (std::hash<int>{}(key.scancode) ^ std::hash<int>{}(key.modifier));
			}
		};

		int scancode;
		int modifier;
	};

	class InputEvent
	{
	public:
		enum class Trigger
		{
			ON_PRESS,
			ON_HOLD,
			ON_RELEASE,
			ON_MOVE
		};

		InputEvent(InputEvents id, Trigger trigger)
			: id(id), trigger(trigger)
		{}

		struct hash
		{
			size_t operator()(const InputEvent& event) const
			{
				return std::hash<std::underlying_type<InputEvents>::type>()(event.id);
			}
		};

		bool operator==(const InputEvent& event) const
		{
			return (this->id == event.id);
		}

		InputEvents GetID() const
		{
			return id;
		}

		Trigger GetTrigger() const
		{
			return trigger;
		}

	protected:
		InputEvents id;
		Trigger trigger;

	};

	class KeyEvent : public InputEvent
	{
	public:
		KeyEvent(InputEvents id, Trigger trigger, Key key)
			: InputEvent(id, trigger), key(key)
		{}

		Key GetKey() const
		{
			return key;
		}

	private:
		Key key;

	};

	class MouseEvent : public InputEvent
	{
	public:
		MouseEvent(InputEvents id)
			: InputEvent(id, Trigger::ON_MOVE)
		{}
	};

	class InputController
	{
	public:
		static InputController& GetInstance();

		// Callbacks
		static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void MouseCallback(GLFWwindow* window, double xpos, double ypos);

		// Events
		void PollEvents();
		void SubscribeTo(InputControllerEvents event, Events::Delegate<void> delegate);
		void SubscribeTo(InputControllerEvents event, Events::Delegate<void, InputEvents> delegate);
		void UnsubscribeTo(InputControllerEvents event, Events::Delegate<void> delegate);
		void UnsubscribeTo(InputControllerEvents event, Events::Delegate<void, InputEvents> delegate);
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

		// Input Cotroller Events //
		std::unique_ptr<Events::Event<void>> EVENT_INPUT_PROCESSED = std::make_unique<Events::Event<void>>();
		std::unique_ptr<Events::Event<void, InputEvents>> EVENT_INPUT_EVENT_POLLED = std::make_unique<Events::Event<void, InputEvents>>();

		std::unordered_set<KeyEvent, InputEvent::hash> key_events
		{
			KeyEvent(InputEvents::ON_HOLD_KEY_W, InputEvent::Trigger::ON_HOLD, Key(GLFW_KEY_W, NULL)),
			KeyEvent(InputEvents::ON_HOLD_KEY_S, InputEvent::Trigger::ON_HOLD, Key(GLFW_KEY_S, NULL)),
			KeyEvent(InputEvents::ON_HOLD_KEY_A, InputEvent::Trigger::ON_HOLD, Key(GLFW_KEY_A, NULL)),
			KeyEvent(InputEvents::ON_HOLD_KEY_D, InputEvent::Trigger::ON_HOLD, Key(GLFW_KEY_D, NULL)),
			KeyEvent(InputEvents::ON_HOLD_KEY_SPACE, InputEvent::Trigger::ON_HOLD, Key(GLFW_KEY_SPACE, NULL)),
			KeyEvent(InputEvents::ON_HOLD_KEY_LCTRL, InputEvent::Trigger::ON_HOLD, Key(GLFW_KEY_LEFT_CONTROL, NULL))
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
