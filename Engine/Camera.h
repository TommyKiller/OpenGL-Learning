#ifndef CAMERA_H
#define CAMERA_H
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include "Window.h"
#include "Position.h"

namespace Graphics
{
	class Camera
	{
	public:
		Camera(Position position, float fov, float near, float far);

		void Move(Position position);

		// Matrices
		glm::mat4 GetViewMat();
		glm::mat4 GetProjectionMat();

	private:
		struct CameraProperties
		{
			CameraProperties(float fov, float near, float far)
				: FoV(fov), Near(near), Far(far)
			{}

			float FoV;
			float Near;
			float Far;
		};

		Position position;
		CameraProperties camera_properties;

	};
}

#endif
