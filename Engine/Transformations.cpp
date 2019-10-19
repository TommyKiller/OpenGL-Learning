#include "Transformations.h"

Graphics::Transformations::Transformations()
	: TranslationMat(glm::mat4(1.0f)), ScaleMat(glm::mat4(1.0f)), RotationMat(glm::mat4(1.0f)) {}

Graphics::Transformations::Transformations(glm::mat4 translation_mat, glm::mat4 scale_mat, glm::mat4 rotation_mat)
	: TranslationMat(translation_mat), ScaleMat(scale_mat), RotationMat(rotation_mat) {}

bool Graphics::Transformations::operator==(const Transformations& value) const
{
	return ((this->TranslationMat == value.TranslationMat)
		&& (this->RotationMat == value.RotationMat)
		&& (this->ScaleMat == value.ScaleMat));
}
