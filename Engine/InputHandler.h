#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H
#include <unordered_map>
#include <memory>
#include "InputController.h"
#include "InputEvents.h"
#include "InputControllerEvents.h"
#include "Event.h"

namespace Input
{
	template<class Type>
	class InputHandler
	{
	public:
		static InputHandler& GetInstance()
		{
			static InputHandler instance;

			return instance;
		}

		void Initialize(std::unordered_map<Type, std::unique_ptr<Events::Event>> events_list,
			std::unordered_map<InputEvents, Type> layout)
		{
			this->events(events_list);
			this->layout(layout);
		}

		// Events
		void PollEvent(InputEvents event)
		{
			(*events[layout[event]])();
		}
		void SubscribeTo(Type event, Events::Delegate delegate)
		{
			(*events[event]) += delegate;
		}
		void UnsubscribeTo(Type event, Events::Delegate delegate)
		{
			(*events[event]) -= delegate;
		}

	private:
		InputHandler()
		{
			InputController::GetInstance().SubscribeTo(InputControllerEvents::INPUT_EVENT_POLLED, Events::Delegate(this, &InputHandler::PollEvent));
		}

		std::unordered_map<Type, std::unique_ptr<Events::Event>> events;
		std::unordered_map<InputEvents, Type> layout;

	};
}

#endif
