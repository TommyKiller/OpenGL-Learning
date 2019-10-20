#ifndef FPSHANDLER_H
#define FPSHANDLER_H
#include <unordered_map>
#include <memory>
#include "Event.h"
#include "InputEvents.h"

namespace Input
{
	enum class FPSInputActions
	{
		ACTION_MOVE_FORWARD,
		ACTION_MOVE_BACKWARD,
		ACTION_MOVE_RIGHT,
		ACTION_MOVE_LEFT,
		ACTION_MOVE_UP,
		ACTION_MOVE_DOWN
	};

	std::unordered_map<InputEvents, FPSInputActions> FPSLayout
	{
		{ InputEvents::ON_HOLD_KEY_W,		FPSInputActions::ACTION_MOVE_FORWARD },
		{ InputEvents::ON_HOLD_KEY_S,		FPSInputActions::ACTION_MOVE_BACKWARD },
		{ InputEvents::ON_HOLD_KEY_D,		FPSInputActions::ACTION_MOVE_RIGHT },
		{ InputEvents::ON_HOLD_KEY_A,		FPSInputActions::ACTION_MOVE_LEFT },
		{ InputEvents::ON_HOLD_KEY_SPACE,	FPSInputActions::ACTION_MOVE_UP },
		{ InputEvents::ON_HOLD_KEY_LCTRL,	FPSInputActions::ACTION_MOVE_DOWN }
	};
}

#endif
