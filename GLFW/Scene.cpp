#include "Scene.h"

Engine::Scene::Scene(glm::mat4 projection)
	: projection(projection)
{}

void Engine::Scene::AddObject(Graphics::Object* actor)
{
	actors.push_back(std::shared_ptr<Graphics::Object>(actor));
}

void Engine::Scene::SetProjection(float fovy, float aspect, float near, float far)
{
	projection = glm::perspective(fovy, aspect, near, far);
}

void Engine::Scene::SetProjection(glm::mat4 projection)
{
	this->projection = projection;
}

std::vector<std::shared_ptr<Graphics::Object>>& Engine::Scene::GetActors()
{
	return actors;
}

glm::mat4 Engine::Scene::GetProjection()
{
	return projection;
}

void Engine::Scene::Dispose()
{
	actors.clear();
}

Engine::Scene::~Scene()
{
	Dispose();
}
