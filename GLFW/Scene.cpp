#include "Scene.h"

Graphics::Scene::Scene(glm::mat4 projection)
	: projection(projection)
{}

void Graphics::Scene::AddObject(Graphics::Object* actor)
{
	actors.push_back(std::shared_ptr<Graphics::Object>(actor));
}

void Graphics::Scene::SetProjection(float fovy, float aspect, float near, float far)
{
	projection = glm::perspective(fovy, aspect, near, far);
}

void Graphics::Scene::SetProjection(glm::mat4 projection)
{
	this->projection = projection;
}

std::vector<std::shared_ptr<Graphics::Object>>& Graphics::Scene::GetActors()
{
	return actors;
}

glm::mat4 Graphics::Scene::GetProjection()
{
	return projection;
}

void Graphics::Scene::Dispose()
{
	actors.clear();
}

Graphics::Scene::~Scene()
{
	Dispose();
}
