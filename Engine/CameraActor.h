#ifndef CAMERAACTOR_H
#define CAMERAACTOR_H
#include "Actor.h"
#include "Camera.h"

namespace Graphics
{
	class CameraActor :	public Actor
	{
	public:
		CameraActor(Position position, float fov, float near, float far);

		// Movement
		void Move() override;

		// CameraControl
		glm::mat4 GetViewMat();
		glm::mat4 GetProjectionMat();

	private:
		static int ca_num;

		std::shared_ptr<Camera> camera;

	};
}

#endif
