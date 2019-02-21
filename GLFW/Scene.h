#ifndef SCENE_H
#define SCENE_H
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <vector>
#include <memory>
#include "Object.h"


namespace Engine
{
	class Scene
	{
	public:
		Scene(glm::mat4 projection = glm::mat4(1));

		void AddObject(Graphics::Object* actor);

		void SetProjection(float fovy, float aspect, float near, float far);

		void SetProjection(glm::mat4 projection);

		std::vector<std::shared_ptr<Graphics::Object>>& GetActors();

		glm::mat4 GetProjection();

		void Dispose();

		~Scene();

	private:
		std::vector<std::shared_ptr<Graphics::Object>> actors;

		glm::mat4 projection;
	};
}


#endif
