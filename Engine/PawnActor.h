#ifndef PAWNACTOR_H
#define PAWNACTOR_H
#include "IRenderable.h"
#include "Actor.h"
#include "Model.h"

namespace Graphics
{
	class PawnActor : public Graphics::Actor, public IRenderable
	{
	public:
		PawnActor(Position position);

		void Render(glm::mat4 projection_mat, glm::mat4 view_mat) override;
		void AssignShader(std::shared_ptr<Shader>& shader) override;

		void LoadModel(const char* file_path);

		// Movement
		void Move() override;

	private:
		static int pa_num;

		std::shared_ptr<Graphics::Model> model;

	};
}

#endif
