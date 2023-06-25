#pragma once

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window
{
	GLFWwindow* const window;

	GLfloat size[2];
	GLfloat scale;
public:
	Window(int width = 640, int height = 480, const char* title = "Sphere");

	virtual	~Window();

	explicit operator bool();

	void swapBuffers()const;

	static void resize(GLFWwindow* const window, int width, int height);

	static void wheel(GLFWwindow* const window, double x, double y);

	const GLfloat* getSize()const;

	GLfloat getScale() const;
};

Window& get_window();