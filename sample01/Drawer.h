#pragma once

#include <GL/glew.h>
#include <memory>
#include <array>

#include "Data.h"

class Drawer
{
	GLuint vao;

	GLuint vertex_vbo;
public:
	struct Vertex
	{
		Vector position;
		Vector color;
	};

	Drawer(GLint size, GLsizei vertex_count, const Vertex* vertex);

	~Drawer();

	Drawer(const Drawer&) = delete;
	Drawer& operator=(const Drawer& obj) = delete;

	void bind() const;

	GLuint get_position_vbo() const;
};
