#include "Object.h"

Graphics::Object::Object(std::shared_ptr<Graphics::Mesh> mesh, glm::vec3 position, glm::vec3 scale,
	glm::vec3 rotation_axis, float rotation_angle)
	: mesh(std::move(mesh)),
	position(position),
	scale(scale),
	rotation_axis(rotation_axis),
	rotation_angle(rotation_angle)
{}

Graphics::Object::Object(Object & object)
{
	this->mesh = object.mesh;
	this->position = object.position;
	this->scale = object.scale;
	this->rotation_axis = object.rotation_axis;
	this->rotation_angle = object.rotation_angle;
}

void Graphics::Object::Scale(glm::vec3 direction)
{
	this->scale = scale;
}

void Graphics::Object::Rotate(float rotation_angle, glm::vec3 rotation_axis)
{
	this->rotation_angle = rotation_angle;
	this->rotation_axis = rotation_axis;
}

void Graphics::Object::Rotate(float rotation_angle)
{
	this->rotation_angle = rotation_angle;
}

void Graphics::Object::MoveTo(glm::vec3 position)
{
	this->position = position;
}

void Graphics::Object::Move(float x, float y, float z)
{
	this->position += glm::vec3(x, y, z);
}

void Graphics::Object::Reset()
{
	position = glm::vec3(0.0f, 0.0f, 0.0f);
	scale = glm::vec3(1.0f, 0.0f, 0.0f);
	rotation_axis = glm::vec3(1.0f, 0.0f, 0.0f);
	rotation_angle = 0;;
}

Graphics::Mesh* Graphics::Object::GetMesh()
{
	return mesh.get();
}

glm::mat4 Graphics::Object::GetModelMat()
{
	glm::mat4 model = glm::translate(glm::mat4(1), position);
	model = glm::rotate(model, rotation_angle, rotation_axis);
	model = glm::scale(model, scale);
	return model;
}

void Graphics::Object::Dispose()
{
	mesh.reset();
	Reset();
}

Graphics::Object::~Object()
{
	Dispose();
}
