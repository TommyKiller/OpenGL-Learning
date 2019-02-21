#ifndef OBJECT_H
#define OBJECT_H
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <memory>
#include "Mesh.h"


namespace Graphics
{
	class Object
	{
	public:
		Object(std::shared_ptr<Graphics::Mesh> mesh, glm::vec3 position = glm::vec3(0.0f), glm::vec3 scale = glm::vec3(1.0f),
			glm::vec3 rotation_axis = glm::vec3(1.0f), float rotation_angle = 0);

		Object(Object& object);

		Mesh* GetMesh();

		glm::mat4 CreateModelMat();

		void Scale(glm::vec3 scale);

		void Rotate(float rotation_angle, glm::vec3 rotation_axis);

		void Rotate(float rotation_angle);

		void MoveTo(glm::vec3 position);

		void Move(float x, float y, float z);

		void Reset();

		void Dispose();

		~Object();

	private:
		std::shared_ptr<Graphics::Mesh> mesh;
		glm::vec3 position;
		glm::vec3 scale;
		glm::vec3 rotation_axis;
		float rotation_angle;
	};
}


#endif
