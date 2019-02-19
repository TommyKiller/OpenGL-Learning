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

		void SetKeyState(int key, bool state);

		bool KeyPressed(int key);

		~InputController();

	private:
		static InputController* instance;

		std::unordered_map<int, bool> keys;

		InputController();

		InputController(InputController&) = delete;
	};
}


#endif
