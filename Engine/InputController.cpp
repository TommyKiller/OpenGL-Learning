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
	if ((key != GLFW_KEY_UNKNOWN) && (action != GLFW_REPEAT))
	{
		Key handled_key(key, mods);
		if (Input::InputController::GetInstance().IsKeyAssigned(handled_key))
		{
			InputEvents event_id = Input::InputController::GetInstance().GetEventID(handled_key);
			InputEvent::Trigger event_trigger = InputController::GetInstance().GetEventTrigger(event_id);
			if (((event_trigger == InputEvent::Trigger::ON_PRESS) || (event_trigger == InputEvent::Trigger::ON_HOLD)) &&
				(action == GLFW_PRESS))
			{
				Input::InputController::GetInstance().SetKeyPressed(handled_key);
				Input::InputController::GetInstance().AddEventToQueue(event_id);
			}
			else if ((event_trigger == InputEvent::Trigger::ON_RELEASE) && (action == GLFW_RELEASE))
			{
				Input::InputController::GetInstance().SetKeyReleased(handled_key);
				Input::InputController::GetInstance().AddEventToQueue(event_id);
			}
		}
	}
}

void Input::InputController::MouseCallback(GLFWwindow* window, double xpos, double ypos)
{
	Input::InputController::GetInstance().SetMouseNewPos(xpos, ypos);
	if (Input::InputController::GetInstance().GetMouseXChange())
	{
		Input::InputController::GetInstance().AddEventToQueue(InputEvents::ON_MOVE_MOUSE_AXIS_X);
	}
	if (Input::InputController::GetInstance().GetMouseYChange())
	{
		Input::InputController::GetInstance().AddEventToQueue(InputEvents::ON_MOVE_MOUSE_AXIS_Y);
	}
}

void Input::InputController::PollEvents()
{
	std::vector<InputEvents> repeat_events;

	while (!events_queue.empty())
	{
		InputEvents event_id = events_queue.front();

		(*ic_events[InputControllerEvents::INPUT_EVENT_POLLED])(event_id);
		if (GetEventTrigger(event_id) == InputEvent::Trigger::ON_HOLD && key_pressed[GetEventKey(event_id)])
		{
			repeat_events.push_back(event_id);
		}

		events_queue.pop();
	}

	(*ic_events[InputControllerEvents::INPUT_PROCESSED])();

	for (const auto& event_id : repeat_events)
	{
		events_queue.push(event_id);
	}
}

void Input::InputController::SubscribeTo(InputControllerEvents event, Events::Delegate delegate)
{
	(*ic_events[event]) += delegate;
}

void Input::InputController::UnsubscribeTo(InputControllerEvents event, Events::Delegate delegate)
{
	(*ic_events[event]) -= delegate;
}

double Input::InputController::GetMouseXChange()
{
	return mouse.xChange;
}

double Input::InputController::GetMouseYChange()
{
	return mouse.yChange;
}

void Input::InputController::SetMouseNewPos(double xpos, double ypos)
{
	mouse.xChange = xpos - mouse.lastXPos;
	mouse.yChange = mouse.lastYPos - ypos;
	mouse.lastXPos = xpos;
	mouse.lastYPos = ypos;
}

Input::InputEvent::Trigger Input::InputController::GetEventTrigger(InputEvents id)
{
	auto key_event = std::find_if(key_events.begin(), key_events.end(),
		[&](const KeyEvent& action) {return (action.GetID() == id); });
	if (key_event != key_events.end())
	{
		return key_event->GetTrigger();
	}
	else
	{
		auto mouse_event = std::find_if(mouse_events.begin(), mouse_events.end(),
			[&](const MouseEvent& action) {return (action.GetID() == id); });

		return mouse_event->GetTrigger();
	}
}

Input::Key Input::InputController::GetEventKey(InputEvents id)
{
	auto key_event = std::find_if(key_events.begin(), key_events.end(),
		[&](const KeyEvent& action) {return (action.GetID() == id); });

	if (key_event != key_events.end())
	{
		return key_event->GetKey();
	}
}

void Input::InputController::AddEventToQueue(InputEvents id)
{
	events_queue.push(id);
}

bool Input::InputController::IsKeyAssigned(Key key)
{
	auto result = std::find_if(key_events.begin(), key_events.end(),
		[&](const KeyEvent& action) {return (action.GetKey() == key); });

	return (result != key_events.end());
}

bool Input::InputController::IsKeyPressed(Key key)
{
	return key_pressed[key];
}

void Input::InputController::SetKeyPressed(Key key)
{
	key_pressed[key] = true;
}

void Input::InputController::SetKeyReleased(Key key)
{
	key_pressed[key] = false;
}

Input::InputEvents Input::InputController::GetEventID(Key key)
{
	auto key_event = std::find_if(key_events.begin(), key_events.end(),
		[&](const KeyEvent& action) {return (action.GetKey() == key); });

	return key_event->GetID();
}
