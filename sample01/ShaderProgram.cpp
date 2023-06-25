#include "ShaderProgram.h"

ShaderProgram::ShaderProgram() : program(glCreateProgram()) {}

bool ShaderProgram::attach_shader(const char* src, GLenum type) const
{
	const GLuint obj = glCreateShader(type);
	glShaderSource(obj, 1, &src, nullptr);
	glCompileShader(obj);

	if (!printShaderInfoLog(obj, "shader"))return false;

	glAttachShader(this->program, obj);
	glDeleteShader(obj);
	return true;
}

bool ShaderProgram::link() const
{
	glLinkProgram(this->program);

	if (printProgramInfoLog(this->program))return true;

	glDeleteProgram(this->program);

	return false;
}

void ShaderProgram::use() const
{
	glUseProgram(this->program);
}

void ShaderProgram::unuse() const
{
	glUseProgram(0);
}

GLint ShaderProgram::get_uniform_location(const char* var_name)
{
	return glGetUniformLocation(this->program, var_name);
}

void ShaderProgram::uniform2f(const char* var_name, GLfloat v0, GLfloat v1) const
{
	GLint location = glGetUniformLocation(this->program, var_name);
	glUniform2f(location, v0, v1);
}

// count 配列数

void ShaderProgram::uniform2fv(const char* var_name, GLsizei count, const GLfloat* value) const
{
	GLint location = glGetUniformLocation(this->program, var_name);
	glUniform2fv(location, count, value);
}

void ShaderProgram::uniform1f(const char* var_name, GLfloat value) const
{
	GLint location = glGetUniformLocation(this->program, var_name);
	glUniform1f(location, value);
}

void ShaderProgram::uniformMat4fv(const char* var_name, GLsizei count, GLboolean transpose, const GLfloat* value) const
{
	GLint location = glGetUniformLocation(this->program, var_name);
	glUniformMatrix4fv(location, count, transpose, value);
}

bool ShaderProgram::readShaderSource(const char* name, std::vector<GLchar>& buffer)
{
	if (name == nullptr)
	{
		return false;
	}

	std::ifstream file(name, std::ios::binary);
	if (file.fail())
	{
		std::cerr << "Error: connot open source file: " << name << std::endl;
		return false;
	}

	file.seekg(0L, std::ios::end);

	GLsizei length = static_cast<GLsizei>(file.tellg());

	buffer.resize(length + 1);

	file.seekg(0L, std::ios::beg);
	file.read(buffer.data(), length);
	buffer[length] = '\0';

	if (file.fail())
	{
		std::cerr << "Error: Could not read source file: " << std::endl;
		file.close();
		return false;
	}

	file.close();
	return true;
}

GLboolean ShaderProgram::printProgramInfoLog(GLuint program) const
{
	// リンク結果
	GLint status;
	glGetShaderiv(program, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		std::cerr << "LNK error" << std::endl;
	}

	// リンクログ長さ
	GLsizei bufSize;
	glGetShaderiv(program, GL_INFO_LOG_LENGTH, &bufSize);

	if (bufSize > 1)
	{
		// ログ内容
		std::vector<GLchar> infoLog(bufSize);
		GLsizei length;
		glGetShaderInfoLog(program, bufSize, &length, &infoLog[0]);
		std::cerr << &infoLog[0] << std::endl;
	}

	return static_cast<GLboolean>(status);
}

// コンパイル結果

GLboolean ShaderProgram::printShaderInfoLog(GLuint shader, const char* str) const
{
	// コンパイル結果
	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		std::cerr << "compile error in " << str << std::endl;
	}

	// コンパイルログ長さ
	GLsizei bufSize;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &bufSize);

	if (bufSize > 1)
	{
		// ログ内容
		std::vector<GLchar> infoLog(bufSize);
		GLsizei length;
		glGetShaderInfoLog(shader, bufSize, &length, &infoLog[0]);
		std::cerr << &infoLog[0] << std::endl;
	}

	return static_cast<GLboolean>(status);
}
