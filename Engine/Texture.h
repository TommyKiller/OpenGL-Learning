#ifndef TEXTURE_H
#define TEXTURE_H
#include <GL/glew.h>
#include <string>
#define STB_IMAGE_IMPLEMENTATION

namespace Graphics
{
	class Texture
	{
	public:
		Texture(GLenum target, std::string path, std::string name);

		const char* GetPath() const;

		std::string GetName() const;

		void Bind() const;

		void Dispose();

		virtual ~Texture();

	protected:
		GLuint id;
		GLenum target;
		std::string name;
		std::string path;
	};
}

#endif
