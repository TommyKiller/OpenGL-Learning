#ifndef MESH_H
#define MESH_H
#include <vector>
#include <GL/glew.h>
#include <memory>
#include "Shader.h"
#include "Vertex.h"
#include "Material.h"

namespace Graphics
{
	class Mesh
	{
	public:
		Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, Material material);

		void Render(std::shared_ptr<Graphics::Shader>& shader);

		void Dispose();

		~Mesh();

	private:
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		Material material;
		GLuint VAO, VBO, EBO;
	};
}

#endif
