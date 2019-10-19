#ifndef MATERIAL_H
#define MATERIAL_H
#include <vector>
#include "Texture2D.h"

namespace Graphics
{
	struct Material
	{
		std::vector<Texture2D> TexturesAmbient;
		std::vector<Texture2D> TexturesDiffuse;
		std::vector<Texture2D> TexturesSpecular;
		float Shininess;

		std::vector<Texture2D> GetAllTextures();
	};
}

#endif
