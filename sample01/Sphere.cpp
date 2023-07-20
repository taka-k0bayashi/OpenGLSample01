#include "Sphere.h"
#include <vector>
#include "Window.h"
#include <glm/gtc/matrix_transform.hpp>

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
	std::vector<GLchar> tcsrc;
	const bool tcstat(ShaderProgram::readShaderSource("Sphere.tesc", tcsrc));
	std::vector<GLchar> tesrc;
	const bool testat(ShaderProgram::readShaderSource("Sphere.tese", tesrc));
	std::vector<GLchar> gsrc;
	const bool gstat(ShaderProgram::readShaderSource("Sphere.geom", gsrc));

	this->program.attach_shader(vsrc.data(), GL_VERTEX_SHADER);
	this->program.attach_shader(fsrc.data(), GL_FRAGMENT_SHADER);
	this->program.attach_shader(tcsrc.data(), GL_TESS_CONTROL_SHADER);
	this->program.attach_shader(tesrc.data(), GL_TESS_EVALUATION_SHADER);
	this->program.attach_shader(gsrc.data(), GL_GEOMETRY_SHADER);
	this->program.link();
}

Sphere::~Sphere()
{
	glDeleteVertexArrays(1, &this->vao);
	glDeleteBuffers(1, &this->vertex_vbo);
	glDeleteBuffers(1, &this->vertex_ibo);
}

void Sphere::draw() const
{
	this->program.use();

	glBindVertexArray(vao);
	float scale = get_window().getScale() / 100;

	glm::mat4 mat = glm::scale(this->proj_mat, glm::vec3(1, 1, 1) * (scale));

	this->program.uniformMat4fv("proj_mat", 1, GL_FALSE, &(mat[0][0]));
	this->program.uniform1f("scale", scale);

	glPatchParameteri(GL_PATCH_VERTICES, 3);
	glDrawElements(GL_PATCHES, 24, GL_UNSIGNED_INT, 0);

	this->program.unuse();
}

void Sphere::update()
{
	this->proj_mat = glm::rotate(this->proj_mat, static_cast<float>(0.01), glm::vec3(0, 0, 1));
}
