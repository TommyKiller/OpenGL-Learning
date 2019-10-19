#ifndef INPUTEVENT_H
#define INPUTEVENT_H
#include "InputEvents.h"
#include "Key.h"

namespace Input
{
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
}

#endif
