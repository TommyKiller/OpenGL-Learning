#ifndef CAMERA_H
#define CAMERA_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>


namespace Engine
{
	class Camera
	{
	public:
		static Camera* GetInstance();

		static void Initialise();

		static void Dispose();

		static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);

	private:
		static Camera* instance;

		glm::mat4 view;

		Camera();

		Camera(Camera&) = delete;

		Camera& operator= (Camera&) = delete;

		~Camera();
	};
}


#endif
