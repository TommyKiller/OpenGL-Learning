#ifndef EDITOR_H
#define EDITOR_H
#include "World.h"
#include "Camera.h"


namespace Engine
{
	class Editor
	{
	public:
		static Editor& GetInstance();

		void EditWorld(std::shared_ptr<Game::World> world);

		void Enable();

		void Disable();

		Graphics::Texture* LoadTexture(GLenum target, const char* filename, bool flip, GLint min_filter, GLint mag_filter, GLint wrap_s, GLint wrap_t);

		void CreateActor();

		void AddActor();

		void Cancel();

	private:
		std::weak_ptr<Game::World> world;
		std::shared_ptr<Game::Actor> active_actor;

		Editor();

		Editor(Editor&) = delete;

		Editor& operator=(Editor&) = delete;

		~Editor();
	};
}


#endif
