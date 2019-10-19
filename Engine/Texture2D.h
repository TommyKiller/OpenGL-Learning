#ifndef TEXTURE2D_H
#define TEXTURE2D_H
#include "Texture.h"

namespace Graphics
{
	class Texture2D : public Texture
	{
	public:
		Texture2D(std::string file_path, std::string name);
	};
}

#endif
