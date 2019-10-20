#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H
#include <unordered_map>
#include <memory>
#include "InputEvents.h"
#include "InputController.h"
#include "Event.h"

namespace Input
{
	template<class EnumType>
	class InputHandler
	{
	public:
		static InputHandler<EnumType>& GetInstance()
		{
			static InputHandler<EnumType> instance;

			return instance;
		}

		void Initialize(std::unordered_map<InputEvents, EnumType> layout)
		{
			this->layout = layout;

			for (const std::pair<InputEvents, EnumType>& pair : layout)
			{
				events.emplace(std::make_pair(pair.second, std::make_unique<Events::Event>()));
			}
		}

		// Events
		void PollEvent(InputEvents event)
		{
			(*events[layout[event]])();
		}
		void SubscribeTo(EnumType event, Events::Delegate delegate)
		{
			(*events[event]) += delegate;
		}
		void UnsubscribeTo(EnumType event, Events::Delegate delegate)
		{
			(*events[event]) -= delegate;
		}

	private:
		InputHandler()
		{
			InputController::GetInstance().SubscribeTo(InputControllerEvents::INPUT_EVENT_POLLED, Events::Delegate(this, &InputHandler<EnumType>::PollEvent));
		};

		std::unordered_map<EnumType, std::unique_ptr<Events::Event>> events;
		std::unordered_map<InputEvents, EnumType> layout;
	};
}

#endif
