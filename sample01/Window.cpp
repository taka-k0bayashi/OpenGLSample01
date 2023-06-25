#include "Window.h"

Window::Window(int width, int height, const char* title)
	:window(glfwCreateWindow(width, height, title, 0, 0)), scale(100.0f)
{
	if (this->window == nullptr)
	{
		std::cerr << "cannot create window" << std::endl;
		exit(1);
	}

	glfwMakeContextCurrent(this->window);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "cannot initialize GLEW" << std::endl;
		exit(1);
	}

	// 垂直同期のタイミング待つ
	glfwSwapInterval(1);

	// このインスタンスのthisを記録する
	glfwSetWindowUserPointer(this->window, this);

	glfwSetWindowSizeCallback(this->window, resize);

	glfwSetScrollCallback(window, wheel);

	resize(this->window, width, height);
}

Window::~Window()
{
	glfwDestroyWindow(this->window);
}

Window::operator bool()
{
	//glfwWaitEvents();
	glfwPollEvents();

	return !glfwWindowShouldClose(window);
}

void Window::swapBuffers() const
{
	glfwSwapBuffers(this->window);
}

void Window::resize(GLFWwindow* const window, int width, int height)
{
	int fbwidth, fbHeight;
	glfwGetFramebufferSize(window, &fbwidth, &fbHeight);

	glViewport(0, 0, fbwidth, fbHeight);

	Window* const instance(static_cast<Window*>(glfwGetWindowUserPointer(window)));

	if (instance != nullptr)
	{
		instance->size[0] = static_cast<GLfloat>(width);
		instance->size[1] = static_cast<GLfloat>(height);
	}
}

void Window::wheel(GLFWwindow* const window, double x, double y)
{
	Window* const instance(static_cast<Window*>(glfwGetWindowUserPointer(window)));

	if (instance != nullptr)
	{
		instance->scale += static_cast<GLfloat>(y);
	}
}

const GLfloat* Window::getSize() const
{
	return this->size;
}

GLfloat Window::getScale() const
{
	return this->scale;
}

Window& get_window()
{
	static Window window(1000, 1000);
	return window;
}
