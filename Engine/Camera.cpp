#include "Camera.h"

Graphics::Camera::Camera(Position position, float fov, float near, float far)
	: position(position), camera_properties(fov, near, far)
{}

void Graphics::Camera::Move(Position position)
{
	this->position = position;
}

glm::mat4 Graphics::Camera::GetViewMat()
{
	static glm::mat4 view_mat = glm::lookAt(position.Pos, position.Pos + position.Front, position.Up);
	static Position cached_positoin = position;

	if (cached_positoin == position)
	{
		return view_mat;
	}
	else
	{
		cached_positoin = position;
		view_mat = glm::lookAt(position.Pos, position.Pos + position.Front, position.Up);
		return view_mat;
	}
}

glm::mat4 Graphics::Camera::GetProjectionMat()
{
	static glm::mat4 projection_mat = glm::perspective(camera_properties.FoV, System::Window::GetInstance().GetAspectRatio(), camera_properties.Near, camera_properties.Far);

	return projection_mat;
}
