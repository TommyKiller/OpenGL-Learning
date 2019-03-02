#include "Model.h"

Graphics::Model::Model(Graphics::Mesh* mesh, glm::vec3 position, glm::vec3 scale,
	glm::vec3 rotation_axis, float rotation_angle)
	: mesh(std::move(mesh)),
	position(position),
	scale(scale),
	rotation_axis(rotation_axis),
	rotation_angle(rotation_angle)
{}

void Graphics::Model::Scale(glm::vec3 direction)
{
	this->scale = scale;
}

void Graphics::Model::Rotate(float rotation_angle, glm::vec3 rotation_axis)
{
	this->rotation_angle = rotation_angle;
	this->rotation_axis = rotation_axis;
}

void Graphics::Model::MoveTo(glm::vec3 position)
{
	this->position = position;
}

void Graphics::Model::Move(glm::vec3 direction, float distance)
{
	this->position += glm::normalize(direction) * distance;
}

Graphics::Mesh* Graphics::Model::GetMesh()
{
	return mesh.get();
}

glm::mat4 Graphics::Model::CalcModelMat()
{
	glm::mat4 model = glm::translate(glm::mat4(1), position);
	model = glm::rotate(model, rotation_angle, rotation_axis);
	model = glm::scale(model, scale);
	return model;
}

void Graphics::Model::Dispose()
{
	mesh.reset(nullptr);
}

Graphics::Model::~Model()
{
	Dispose();
}
