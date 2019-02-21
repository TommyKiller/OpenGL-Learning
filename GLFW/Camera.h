#ifndef CAMERA_H
#define CAMERA_H
#include <GL/glew.h>
#include <GLM/glm.hpp>


namespace Engine
{
	class Camera
	{
	public:
		static Camera* GetInstance();

		static void Initialise();

		static void Dispose();

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
