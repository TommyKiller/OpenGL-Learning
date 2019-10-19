#ifndef FPSINPUT_H
#define FPSINPUT_H
#include <unordered_map>
#include <memory>
#include "Event.h"
#include "InputEvents.h"

namespace Input
{
	enum class FPSEvents
	{
		EVENT_MOVE_FORWARD,
		EVENT_MOVE_BACKWARD,
		EVENT_MOVE_RIGHT,
		EVENT_MOVE_LEFT,
		EVENT_MOVE_UP,
		EVENT_MOVE_DOWN
	};

	std::unordered_map<FPSEvents, std::unique_ptr<Events::Event>> fps_events
	{
		{ FPSEvents::EVENT_MOVE_FORWARD,	std::make_unique<Events::Event>() },
		{ FPSEvents::EVENT_MOVE_BACKWARD,	std::make_unique<Events::Event>() },
		{ FPSEvents::EVENT_MOVE_RIGHT,		std::make_unique<Events::Event>() },
		{ FPSEvents::EVENT_MOVE_LEFT,		std::make_unique<Events::Event>() },
		{ FPSEvents::EVENT_MOVE_UP,			std::make_unique<Events::Event>() },
		{ FPSEvents::EVENT_MOVE_DOWN,		std::make_unique<Events::Event>() },
	};
	std::unordered_map<InputEvents, FPSEvents> fps_layout
	{
		{ InputEvents::ON_HOLD_KEY_W,		FPSEvents::EVENT_MOVE_FORWARD },
		{ InputEvents::ON_HOLD_KEY_S,		FPSEvents::EVENT_MOVE_BACKWARD },
		{ InputEvents::ON_HOLD_KEY_D,		FPSEvents::EVENT_MOVE_RIGHT },
		{ InputEvents::ON_HOLD_KEY_A,		FPSEvents::EVENT_MOVE_LEFT },
		{ InputEvents::ON_HOLD_KEY_SPACE,	FPSEvents::EVENT_MOVE_UP },
		{ InputEvents::ON_HOLD_KEY_LCTRL,	FPSEvents::EVENT_MOVE_DOWN },
	};
}

#endif
