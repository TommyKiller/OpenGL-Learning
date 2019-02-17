#include "Mesh.h"

Graphics::Mesh::Mesh(Mesh& mesh)
{
	VAO = mesh.VAO;
	EBO = mesh.EBO;
	VBOs = mesh.VBOs;
	VBOs_count = mesh.VBOs_count;
	elements_count = mesh.elements_count;
}

Graphics::Mesh::Mesh(GLfloat* vertecies_coords, unsigned int vcoords_count, GLfloat* vertecies_colours, unsigned int vcolours_count,
	GLuint* elements, unsigned int elements_count, GLenum usage)
	: elements_count(elements_count), VBOs_count(2)
{
	VBOs = new GLuint[VBOs_count]
	{
		CreateBuffer(GL_VERTEX_ARRAY, vertecies_coords, vcoords_count, usage),
		CreateBuffer(GL_VERTEX_ARRAY, vertecies_colours, vcolours_count, usage)
	};
	EBO = CreateBuffer(GL_ELEMENT_ARRAY_BUFFER, elements, elements_count, usage);
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glBindVertexArray(0);
}

void Graphics::Mesh::Render() const
{
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, elements_count, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Graphics::Mesh::Dispose()
{
	if (VAO != 0)
	{
		glDeleteVertexArrays(1, &VAO);
		VAO = 0;
	}
	if (EBO != 0)
	{
		glDeleteBuffers(1, &EBO);
		EBO = 0;
	}
	if (VBOs[0] != 0)
	{
		glDeleteBuffers(VBOs_count, VBOs);
		delete[] VBOs;
	}

	elements_count = 0;
	VBOs_count = 0;
}

Graphics::Mesh::~Mesh()
{
	Dispose();
}
