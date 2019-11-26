#include "Scene.h"

Graphics::Scene& Graphics::Scene::GetInstance()
{
	static Graphics::Scene instance;

	return instance;
}

void Graphics::Scene::Render()
{
	if (auto camera = user_camera.lock())
	{
		(*events[SceneEvents::EVENT_SCENE_RENDER])(camera->GetProjectionMat(), camera->GetViewMat());
	}
}

void Graphics::Scene::SetUserCamera(ActorID actor_id)
{
	user_camera = GetCameraActor(actor_id);
}

void Graphics::Scene::AddShader(std::shared_ptr<Shader> shader)
{
	shaders.push_back(shader);
}

void Graphics::Scene::AddActor(std::shared_ptr<PawnActor> actor)
{
	pawn_actors.push_back(actor);
	std::function<void(glm::mat4, glm::mat4)> member_func = [actor](glm::mat4 projection_mat, glm::mat4 view_mat) {return actor.get()->Render(projection_mat, view_mat); };
	SubscribeTo(SceneEvents::EVENT_SCENE_RENDER, Events::Delegate(member_func, &PawnActor::Render, actor.get()));
}

void Graphics::Scene::AddActor(std::shared_ptr<CameraActor> actor)
{
	camera_actors.push_back(actor);
}

std::shared_ptr<Graphics::PawnActor>& Graphics::Scene::GetPawnActor(ActorID id)
{
	auto result = std::find_if(pawn_actors.begin(), pawn_actors.end(), [&](const std::shared_ptr<PawnActor>& actor) { return (actor->GetID() == id); });
	return pawn_actors[std::distance(pawn_actors.begin(), result)];
}

std::shared_ptr<Graphics::CameraActor>& Graphics::Scene::GetCameraActor(ActorID id)
{
	auto result = std::find_if(camera_actors.begin(), camera_actors.end(), [&](const std::shared_ptr<CameraActor>& actor) { return (actor->GetID() == id); });
	return camera_actors[std::distance(camera_actors.begin(), result)];
}

std::shared_ptr<Graphics::Shader>& Graphics::Scene::GetShader(GLuint id)
{
	auto result = std::find_if(shaders.begin(), shaders.end(), [&](const std::shared_ptr<Shader>& shader) { return (shader->GetID() == id); });
	return shaders[std::distance(shaders.begin(), result)];
}
// Subscribe on events //
void Graphics::Scene::SubscribeTo(SceneEvents event, Events::Delegate<void, glm::mat4, glm::mat4> delegate)
{
	(*events[event]) += delegate;
}
//---------------------//
void Graphics::Scene::UnsubscribeTo(SceneEvents event, Events::Delegate<void, glm::mat4, glm::mat4> delegate)
{
	(*events[event]) += delegate;
}
// END Subscribe on events //