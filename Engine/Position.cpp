#include "Position.h"

//Graphics::Position::Position()
//	: Pos(0.0f, 0.0f, 0.0f),
//	Front(0.0f, 0.0f, 1.0f),
//	Right(1.0f, 0.0f, 0.0f),
//	Up(0.0f, 1.0f, 0.0f)
//{}

Graphics::Position::Position(glm::vec3 pos, glm::vec3 front, glm::vec3 world_up)
	: Pos(pos)
{
	Front = glm::normalize(Front);
	Right = glm::normalize(glm::cross(world_up, Front));
	Up = glm::normalize(glm::cross(Front, Right));
}

bool Graphics::Position::operator==(Position& position)
{
	return ((this->Pos == position.Pos) && (this->Front == position.Front) &&
		(this->Right == position.Right) && (this->Up == position.Up));
}

bool Graphics::Position::operator!=(Position& position)
{
	return ((this->Pos != position.Pos) || (this->Front != position.Front) ||
		(this->Right != position.Right) || (this->Up != position.Up));;
}
