#include "Texture.h"

Graphics::Texture::Texture(GLenum target)
	: target(target)
{
	glGenTextures(1, &ID);
}

void Graphics::Texture::SetFilters(GLint min_filter, GLint mag_filter)
{
	glBindTexture(target, ID);

	glTexParameteri(target, GL_TEXTURE_MIN_FILTER, min_filter);
	glTexParameteri(target, GL_TEXTURE_MAG_FILTER, mag_filter);

	glBindTexture(target, 0);
}

void Graphics::Texture::SetWraps(GLint wrap_s, GLint wrap_t)
{
	glBindTexture(target, ID);

	glTexParameteri(target, GL_TEXTURE_WRAP_S, wrap_s);
	glTexParameteri(target, GL_TEXTURE_WRAP_T, wrap_t);

	glBindTexture(target, 0);
}

void Graphics::Texture::CustomMipmaps(std::map<Graphics::Image*, GLint> mipmaps)
{
	for (auto&& [image, mipmap_level] : mipmaps)
	{
		glTexImage2D(target, mipmap_level, image->GetFormat(), image->GetWidth(), image->GetHeight(), 0, image->GetFormat(), GL_UNSIGNED_BYTE, image->GetData());
		glGenerateMipmap(target);
	}
}

void Graphics::Texture::AutoMipmaps(Graphics::Image* image)
{
	glTexImage2D(target, 0, image->GetFormat(), image->GetWidth(), image->GetHeight(), 0, image->GetFormat(), GL_UNSIGNED_BYTE, image->GetData());
	glGenerateMipmap(target);
}

Graphics::Texture::Texture(Texture& texture) : ID(texture.ID), target(texture.target){}

void Graphics::Texture::Use()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(target, ID);
}

void Graphics::Texture::Dispose()
{
	if (ID != 0)
	{
		glDeleteTextures(1, &ID);
		ID = 0;
	}
}

Graphics::Texture::~Texture()
{
	Dispose();
}
