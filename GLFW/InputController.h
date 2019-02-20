#ifndef INPUTCONTROLLER_H
#define INPUTCONTROLLER_H
#include <GLFW/glfw3.h>
#include <unordered_map>


namespace Engine
{
	class InputController
	{
	public:
		static InputController& GetInstance();

		static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

		void SetKeyHandled(int key, bool handled);

		int GetKeyMods(int key);

		bool KeyModded(int key);

		bool KeyPressed(int key);

		bool KeyHandled(int key);

	private:
		struct Key
		{
			int scancode;
			int mods;
			bool modded;
			bool pressed;
			bool handled;
		};

		std::unordered_map<int, Key> keys;

		void AddKey(int key, int scancode);

		void SetKeyDefalut(int key);

		void SetKeyPressed(int key, bool pressed);

		void SetKeyMods(int key, int mods);

		bool HasKey(int key);

		InputController();

		InputController(InputController&) = delete;

		InputController& operator=(const InputController&) = delete;

		~InputController();
	};
}


#endif
