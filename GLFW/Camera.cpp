#include "Camera.h"

Graphics::Camera& Graphics::Camera::GetInstance()
{
	static Graphics::Camera instance;

	return instance;
}

void Graphics::Camera::Initialise(glm::vec3 position, glm::vec3 worldUp, GLfloat yaw, GLfloat pitch, GLfloat moveSpeed, GLfloat turnSpeed)
{
	this->position = position;
	this->worldUp = worldUp;
	this->yaw = yaw;
	this->pitch = pitch;
	this->moveSpeed = moveSpeed;
	this->turnSpeed = turnSpeed;
	UpdatePosition();
	Input::InputController::GetInstance().SubscribeTo(Input::EVENT_MOVE, new Events::Delegate(this, &Graphics::Camera::Move));
}

void Graphics::Camera::Bind()
{
	Input::InputController::GetInstance().UnsubscribeTo(Input::EVENT_MOVE, new Events::Delegate(this, &Graphics::Camera::Move));
}

void Graphics::Camera::Unbind()
{
	Input::InputController::GetInstance().SubscribeTo(Input::EVENT_MOVE, new Events::Delegate(this, &Graphics::Camera::Move));
}

void Graphics::Camera::UpdatePosition()
{
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(front);

	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
}

void Graphics::Camera::MoveToPos(glm::vec3 position, GLfloat yaw, GLfloat pitch)
{
	this->position = position;
	this->yaw = yaw;
	this->pitch = pitch;
}

void Graphics::Camera::Move()
{
	using namespace Input;
	GLfloat velocity = System::GetDeltaTime() * moveSpeed;
	if (InputController::GetInstance().KeyPressed(InputController::GetInstance().GetKey(ACTION_MOVE_FORWARD)))
	{
		position += front * velocity;
	}
	if (InputController::GetInstance().KeyPressed(InputController::GetInstance().GetKey(ACTION_MOVE_BACKWARD)))
	{
		position -= front * velocity;
	}
	if (InputController::GetInstance().KeyPressed(InputController::GetInstance().GetKey(ACTION_MOVE_LEFT)))
	{
		position -= right * velocity;
	}
	if (InputController::GetInstance().KeyPressed(InputController::GetInstance().GetKey(ACTION_MOVE_RIGHT)))
	{
		position += right * velocity;
	}
}

glm::mat4 Graphics::Camera::CalcViewMat()
{
	return glm::lookAt(position, position + front, up);
}

Graphics::Camera::Camera()
{}

Graphics::Camera::~Camera()
{}
