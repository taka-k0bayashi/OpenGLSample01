#pragma once
#include <GL/glew.h>
#include "glm/mat4x4.hpp"
#include <memory>
#include <array>

#include "Shape.h"
#include "ShaderProgram.h"

class Sphere : public Shape
{
private:

	GLuint vao;

	GLuint vertex_vbo;

	GLuint vertex_ibo;

	ShaderProgram program;
	
	glm::mat4 proj_mat;

public:
	struct Vertex
	{
		glm::vec3 position;
		glm::vec3 color;
	};

	using Edge = glm::ivec2;

	Sphere(GLsizei vertex_count, const Vertex* vertex, GLsizei vertex_index_size, const Edge* edge, const glm::mat4& proj_mat);

	~Sphere();

	Sphere(const Sphere&) = delete;
	Sphere& operator=(const Sphere& obj) = delete;

	void draw() const override;
};

