#include "Texture2D.h"
#include <stdexcept>
#include <string>
#include "stb/stb_image.h"

Graphics::Texture2D::Texture2D(std::string file_path, std::string name)
	: Texture(GL_TEXTURE_2D, file_path, "2D" + name)
{
	int width, height, nrChannels;
	unsigned char* data = stbi_load(file_path.c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{
		GLenum format;
		switch (nrChannels)
		{
		case 1:
			format = GL_RED;
			break;
		case 3:
			format = GL_RGB;
			break;
		case 4:
			format = GL_RGBA;
			break;
		default:
			format = 0;
		}

		glBindTexture(target, id);
		glTexImage2D(target, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(target);

		glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::string error_msg("Failed to load an image at ");
		error_msg += file_path;
		throw std::exception(error_msg.c_str());
	}
}
