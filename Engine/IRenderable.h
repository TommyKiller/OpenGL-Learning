#ifndef IRENDERABLE_H
#define IRENDERABLE_H
#include <GLM/glm.hpp>
#include <memory>
#include "Shader.h"

namespace Graphics
{
	class IRenderable
	{
	public:
		virtual void Render(glm::mat4 projection_mat, glm::mat4 view_mat) = 0;

		virtual void AssignShader(std::shared_ptr<Shader>& shader) = 0;

		virtual ~IRenderable() = 0;

		std::weak_ptr<Shader> assigned_shader;
	};
}

#endif
