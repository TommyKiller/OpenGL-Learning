#ifndef INPUTCONTROLLER_H
#define INPUTCONTROLLER_H
#include <GLFW/glfw3.h>
#include <unordered_map>


namespace Input
{
	class InputController
	{
	public:
		static InputController* GetInstance();

		static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

		void SetKeyPressedState(int key, bool state);

		void SetKeyHandledState(int key, bool state);

		bool IsPressed(int key);

		int IsHandled(int key);

		~InputController();

	private:
		static InputController* instance;

		std::unordered_map<int, bool> keys_pressed;

		std::unordered_map<int, bool> keys_handled;

		InputController();

		InputController(InputController&) = delete;
	};
}


#endif
