#ifndef TEXTURE_H
#define TEXTURE_H
#include <map>
#include <GL/glew.h>
#include "Image.h"
#include "Editor.h"


namespace Graphics
{
	class Texture
	{
	private:
		GLenum target;
		GLuint ID;

		Texture(GLenum target);

		void SetFilters(GLint min_filter, GLint mag_filter);

		void SetWraps(GLint wrap_s, GLint wrap_t);

		void CustomMipmaps(std::map<Graphics::Image*, GLint> mipmaps);

		void AutoMipmaps(Graphics::Image* image);

	public:
		Texture(Texture& texture);

		void Use();

		void Dispose();

		~Texture();

		friend Engine::Editor;
	};
}


#endif
