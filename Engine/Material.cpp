#include "Material.h"

std::vector<Graphics::Texture2D> Graphics::Material::GetAllTextures()
{
	std::vector<Texture2D> textures;
	textures.insert(textures.end(), TexturesAmbient.begin(), TexturesAmbient.end());
	textures.insert(textures.end(), TexturesDiffuse.begin(), TexturesDiffuse.end());
	textures.insert(textures.end(), TexturesSpecular.begin(), TexturesSpecular.end());
	return textures;
}
