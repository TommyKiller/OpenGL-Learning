#ifndef VERTEX_H
#define VERTEX_H
#include <GLM/glm.hpp>
#include <vector>

namespace Graphics
{
	struct Vertex
	{
		Vertex(glm::vec3 position, glm::vec3 normal, glm::vec3 tangent, glm::vec3 bitangent, std::vector<glm::vec2> texCoords)
			: Position(position), Normal(normal), Tangent(tangent), Bitangent(bitangent), TexCoords(texCoords) {}

		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec3 Tangent;
		glm::vec3 Bitangent;
		std::vector<glm::vec2> TexCoords;
	};
}

#endif
