#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H
#include <unordered_map>
#include <memory>
#include "InputEvents.h"
#include "InputController.h"
#include "utilities/Event.h"

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

			for (const std::pair<InputEvents, EnumType>&& pair : layout)
			{
				events.emplace(std::make_pair(pair.second, std::make_unique<Events::Event<void>>()));
			}
		}

		// Events
		void PollEvent(InputEvents event)
		{
			(*events[layout[event]])();
		}
		void SubscribeTo(EnumType event, Events::Delegate<void> delegate)
		{
			(*events[event]) += delegate;
		}
		void UnsubscribeTo(EnumType event, Events::Delegate<void> delegate)
		{
			(*events[event]) -= delegate;
		}

	private:
		InputHandler()
		{
			std::function<void(InputEvents)> member_func = [this](InputEvents event) { return this->PollEvent(event); };
			InputController::GetInstance().SubscribeTo(InputControllerEvents::INPUT_EVENT_POLLED, Events::Delegate(member_func, &InputHandler<EnumType>::PollEvent, this));
		};

		std::unordered_map<EnumType, std::unique_ptr<Events::Event<void>>> events;
		std::unordered_map<InputEvents, EnumType> layout;
	};
}

#endif
