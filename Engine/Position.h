#ifndef POSITION_H
#define POSITION_H
#include <GLM/glm.hpp>

namespace Graphics
{
	struct Position
	{
		//Position();
		Position(glm::vec3 pos, glm::vec3 front, glm::vec3 world_up);

		bool operator==(Position& position);
		bool operator!=(Position& position);

		glm::vec3 Pos;
		glm::vec3 Front;
		glm::vec3 Right;
		glm::vec3 Up;
	};
}

#endif
