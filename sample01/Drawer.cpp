#include "Drawer.h"

inline Drawer::Drawer(GLint size, GLsizei vertex_count, const Vertex* vertex) : vao(), vertex_vbo()
{
	glGenVertexArrays(1, &this->vao);
	glBindVertexArray(this->vao);

	glGenBuffers(1, &this->vertex_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, this->vertex_vbo);
	glBufferData(GL_ARRAY_BUFFER, vertex_count * sizeof(Vertex), vertex, GL_STATIC_DRAW);

	glVertexAttribPointer(0, size, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
}

inline Drawer::~Drawer()
{
	glDeleteVertexArrays(1, &this->vao);
	glDeleteBuffers(1, &this->vertex_vbo);
}

inline void Drawer::bind() const
{
	glBindVertexArray(vao);
}

inline GLuint Drawer::get_position_vbo() const {
	return this->vertex_vbo;
}
