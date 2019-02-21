#include "Render.h"

Graphics::Render::Render()
{}

Graphics::Render::~Render()
{}

Graphics::Render& Graphics::Render::GetInstance()
{
	static Graphics::Render instance;

	return instance;
}

void Graphics::Render::FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	int xpos, ypos;
	glfwGetWindowPos(window, &xpos, &ypos);
	Graphics::Render::GetInstance().ReshapeViewport(xpos, ypos, width, height);
}

void Graphics::Render::Unbind()
{
	glBindVertexArray(0);
	glUseProgram(0);
}

void Graphics::Render::ReshapeViewport(int xpos, int ypos, int width, int height)
{
	glViewport(xpos, ypos, width, height);
}

void Graphics::Render::ClearColor(glm::vec4 clear_color)
{
	glClearColor(clear_color.r, clear_color.g, clear_color.b, clear_color.a);
}

void Graphics::Render::Enable(GLenum cap)
{
	glEnable(cap);
}

void Graphics::Render::operator()(ShaderProgram* shader_program, Graphics::Object* object, glm::mat4 projection)
{
	shader_program->Use();
	shader_program->SetUniform("projection", 1, GL_FALSE, projection);
	object->GetMesh()->Use();
	shader_program->SetUniform("model", 1, GL_FALSE, object->CreateModelMat());
	glDrawElements(GL_TRIANGLES, object->GetMesh()->GetElementsCount(), GL_UNSIGNED_INT, 0);
	Unbind();
}

void Graphics::Render::operator()(ShaderProgram* shader_program, Engine::Scene* scene)
{
	shader_program->Use();
	shader_program->SetUniform("projection", 1, GL_FALSE, scene->GetProjection());
	std::for_each(scene->GetActors().begin(), scene->GetActors().end(), [&shader_program](std::shared_ptr<Graphics::Object> actor)
		{
			actor->GetMesh()->Use();
			shader_program->SetUniform("model", 1, GL_FALSE, actor->CreateModelMat());
			glDrawElements(GL_TRIANGLES, actor->GetMesh()->GetElementsCount(), GL_UNSIGNED_INT, 0);
		});
	Unbind();
}
