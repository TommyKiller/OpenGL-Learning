#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H
#include <GLM/glm.hpp>

namespace Graphics
{
	struct Transformations
	{
		Transformations();
		Transformations(glm::mat4 translation_mat, glm::mat4 scale_mat, glm::mat4 rotation_mat);

		bool operator==(const Transformations& value) const;

		glm::mat4 TranslationMat;
		glm::mat4 ScaleMat;
		glm::mat4 RotationMat;
	};
}

#endif
