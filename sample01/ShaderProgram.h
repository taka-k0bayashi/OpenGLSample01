#pragma once

#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h> 
#include <GL/glut.h>
#include <fstream>

class ShaderProgram
{
	GLuint program;
public:
	ShaderProgram();

	bool attach_shader(const char* src, GLenum type) const;

	bool link() const;

	void use() const;

	void unuse() const;

	GLint get_uniform_location(const char* var_name);

	void uniform2f(const char* var_name, GLfloat v0, GLfloat v1) const;
	// count 配列数
	void uniform2fv(const char* var_name, GLsizei count, const GLfloat* value) const;

	void uniform1f(const char* var_name, GLfloat value) const;

	void uniformMat4fv(const char* var_name, GLsizei count, GLboolean transpose, const GLfloat* value) const;

	static bool readShaderSource(const char* name, std::vector<GLchar>& buffer);
private:
	GLboolean printProgramInfoLog(GLuint program) const;

	// コンパイル結果
	GLboolean printShaderInfoLog(GLuint shader, const char* str) const;
};
