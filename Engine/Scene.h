#ifndef SCENE_H
#define SCENE_H
#include <map>
#include <memory>
#include "Actors.h"
#include "CameraActor.h"
#include "SceneEvents.h"
#include "utilities/Event.h"

namespace Graphics
{
	class Scene
	{
	public:
		static Scene& GetInstance();

		void Render();
		void SetUserCamera(ActorID actor_id);

		// Adding instances
		void AddShader(std::shared_ptr<Shader> shader);
		void AddActor(std::shared_ptr<PawnActor> actor);
		void AddActor(std::shared_ptr<CameraActor> actor);

		std::shared_ptr<Graphics::PawnActor>& GetPawnActor(ActorID id);     // NEED
		std::shared_ptr<Graphics::CameraActor>& GetCameraActor(ActorID id); // TO ADD
		std::shared_ptr<Graphics::Shader>& GetShader(GLuint id);			// CHECK ON EXISTANCE

		// Events
		void SubscribeTo(SceneEvents event, Events::Delegate<void, glm::mat4, glm::mat4> delegate);
		void UnsubscribeTo(SceneEvents event, Events::Delegate<void, glm::mat4, glm::mat4> delegate);

	private:
		std::unordered_map<SceneEvents, std::unique_ptr<Events::Event<void, glm::mat4, glm::mat4>>> events = make_unordered_map
		(
			std::make_pair(SceneEvents::EVENT_SCENE_RENDER, std::make_unique<Events::Event<void, glm::mat4, glm::mat4>>())
		);

		std::vector<std::shared_ptr<PawnActor>> pawn_actors;
		std::vector<std::shared_ptr<CameraActor>> camera_actors;
		std::vector<std::shared_ptr<Shader>> shaders;
		std::weak_ptr<CameraActor> user_camera;

		Scene();
		Scene(Scene&) = delete;
		Scene& operator=(const Scene&) = delete;
	};
}

#endif
