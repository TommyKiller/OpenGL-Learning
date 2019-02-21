#ifndef MESH_H
#define MESH_H
#include <GL/glew.h>
#include <utility>


namespace Graphics
{
	class Mesh
	{
	public:
		Mesh() = delete;

		Mesh(Mesh& mesh);

		Mesh(std::pair<GLfloat*, unsigned int>* vertex_buffers, unsigned int vertex_buffers_count,
			GLuint* elements, unsigned int elements_count, GLenum usage);

		GLuint GetVAO();

		unsigned int GetElementsCount() const;

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

		GLuint CreateVAO(GLuint* VBO, unsigned int VBO_count, GLuint EBO);

		void Dispose();

		~Mesh();
	private:
		GLuint VAO, EBO;

		GLuint* VBOs;

		unsigned int elements_count, VBOs_count;
	};
}


#endif
