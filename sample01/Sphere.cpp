#include "Sphere.h"
#include <vector>


Sphere::Sphere(GLsizei vertex_count, const Vertex* vertex, GLsizei edge_count, const Edge* edge, const glm::mat4& proj_mat) : vao(), vertex_vbo(), vertex_ibo(), program(), proj_mat(proj_mat)
{
	glGenVertexArrays(1, &this->vao);
	glBindVertexArray(this->vao);

	glGenBuffers(1, &this->vertex_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, this->vertex_vbo);
	glBufferData(GL_ARRAY_BUFFER, vertex_count * sizeof(Vertex), vertex, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
	glEnableVertexAttribArray(1);

	glGenBuffers(1, &this->vertex_ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->vertex_ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, edge_count * sizeof(Edge), edge, GL_STATIC_DRAW);

	glBindVertexArray(0);

	std::vector<GLchar> vsrc;
	const bool vstat(ShaderProgram::readShaderSource("Sphere.vert", vsrc));
	std::vector<GLchar> fsrc;
	const bool fstat(ShaderProgram::readShaderSource("Sphere.frag", fsrc));

	this->program.attach_shader(vsrc.data(), GL_VERTEX_SHADER);
	this->program.attach_shader(fsrc.data(), GL_FRAGMENT_SHADER);
	this->program.link();
}

Sphere::~Sphere()
{
	glDeleteVertexArrays(1, &this->vao);
	glDeleteBuffers(1, &this->vertex_vbo);
}

void Sphere::draw() const
{
	this->program.use();

	glBindVertexArray(vao);

	this->program.uniformMat4fv("proj_mat", 1, GL_FALSE, &(this->proj_mat[0][0]));

	glDrawElements(GL_LINES, 24, GL_UNSIGNED_INT, 0);

	this->program.unuse();
}