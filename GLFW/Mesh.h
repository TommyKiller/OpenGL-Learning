#ifndef MESH_H
#define MESH_H
#include <GL/glew.h>

namespace Graphics
{
	class Mesh
	{
	public:
		Mesh() = delete;

		Mesh(Mesh& mesh);

		Mesh(GLfloat* vertecies_coords, unsigned int vcoords_count, GLfloat* vertecies_colours, unsigned int vcolours_count,
			GLuint* elements, unsigned int elements_count, GLenum usage);

		void Render() const;

		template<class data_t>
		GLuint CreateBuffer(GLenum target, data_t* data, unsigned int data_count, GLenum usage)
		{
			GLuint BO;
			glGenBuffers(1, &BO);

			glBindBuffer(target, BO);
			glBufferData(target, sizeof(data_t) * data_count, data, usage);
			glBindBuffer(target, 0);

			return BO;
		}

		void Dispose();

		~Mesh();
	private:
		GLuint VAO, EBO;

		GLuint* VBOs;

		GLsizei elements_count, VBOs_count;
	};
}


#endif
