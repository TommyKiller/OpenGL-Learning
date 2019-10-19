#ifndef KEY_H
#define KEY_H
#include <GLFW/glfw3.h>
#include <functional>

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
}

#endif
