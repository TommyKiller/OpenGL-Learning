#include "Texture.h"

Graphics::Texture::Texture(GLenum target, std::string path, std::string name)
	: target(target), path(path), name(name)
{
	glGenTextures(1, &id);
}

const char* Graphics::Texture::GetPath() const
{
	return path.c_str();
}

std::string Graphics::Texture::GetName() const
{
	return name;
}

void Graphics::Texture::Bind() const
{
	glBindTexture(target, id);
}

void Graphics::Texture::Dispose()
{
	if (id != 0)
	{
		glDeleteTextures(1, &id);
		id = 0;
	}
}

Graphics::Texture::~Texture()
{
	Dispose();
}
