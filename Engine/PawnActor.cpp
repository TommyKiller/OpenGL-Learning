#include "PawnActor.h"

int Graphics::PawnActor::pa_num = 0;

Graphics::PawnActor::PawnActor(Position position)
	: Actor(std::string("PAWN_ACTOR_" + pa_num++), position)
{}

void Graphics::PawnActor::Render(glm::mat4 projection_mat, glm::mat4 view_mat)
{
	if (auto shader = assigned_shader.lock())
	{
		shader->Bind();
		shader->SetUniform("projection_mat", projection_mat);
		shader->SetUniform("view_mat", view_mat);
		model->Render(shader);
		shader->Unbind();
	}
}

void Graphics::PawnActor::AssignShader(std::shared_ptr<Shader>& shader)
{
	assigned_shader = shader;
}

void Graphics::PawnActor::LoadModel(const char* file_path)
{
	model = std::make_shared<Graphics::Model>(file_path);
	model->Translate(position.Pos);
}

void Graphics::PawnActor::Move()
{
	static Position cached_position = position;
	if (position != cached_position)
	{
		cached_position = position;
		model->Translate(position.Pos);
		Actor::Move();
	}
}
