#ifndef INPUT_H
#define INPUT_H
#include <memory>
#include <unordered_map>
#include "Event.h"
#include "InputHandler.h"
#include "FPSHandler.h"

namespace Input
{
	template<class EnumType>
	void Initialize(std::unordered_map<Input::InputEvents, EnumType> layout)
	{
		Input::InputHandler<EnumType>::GetInstance().Initialize(layout);
	}
}

#endif
