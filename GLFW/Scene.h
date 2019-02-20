#ifndef SCENE_H
#define SCENE_H
#include <GLM/glm.hpp>


namespace Engine
{
	class Scene
	{
	public:
		Scene();
		~Scene();

	private:
		glm::mat4 projection;
	};
}


#endif
