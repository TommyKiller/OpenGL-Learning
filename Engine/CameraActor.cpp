#include "CameraActor.h"

int Graphics::CameraActor::ca_num = 0;

Graphics::CameraActor::CameraActor(Position position, float fov, float near, float far)
	: Actor(std::string("CAMERA_ACTOR_" + ca_num), position)
{
	camera = std::make_shared<Camera>(position, fov, near, far);
}

void Graphics::CameraActor::Move()
{
	static Position cached_position = position;
	if (position != cached_position)
	{
		cached_position = position;
		camera->Move(position);
		Actor::Move();
	}
}

glm::mat4 Graphics::CameraActor::GetViewMat()
{
	return camera->GetViewMat();
}

glm::mat4 Graphics::CameraActor::GetProjectionMat()
{
	return camera->GetProjectionMat();
}
