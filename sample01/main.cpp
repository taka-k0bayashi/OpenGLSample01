#include <cstdlib>
#include <iostream>
#include <vector>
#include <memory>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Window.h"
#include "ShaderProgram.h"

#include "Sphere.h"

namespace
{
	const std::vector<Sphere::Vertex>& get_vertices()
	{
		static std::vector<Sphere::Vertex> vertices =
		{
			{ { 0, 0, 1}, {1.0,  0,  0} },
			{ { 1, 0, 0}, {1.0,1.0,0.0} },
			{ { 0, 1, 0}, {  0,1.0,0.0} },
			{ {-1, 0, 0}, {0.0,1.0,1.0} },
			{ { 0,-1, 0}, {0.0,1.0,0.0} },
			{ { 0, 0,-1}, {0.0,  0,1.0} }
		};
		return vertices;
	}

	const std::vector<Sphere::Edge>& get_edges()
	{
		static std::vector<Sphere::Edge> edges =
		{
			{ 0,1,2 },
			{ 0,2,3 },
			{ 0,3,4 },
			{ 0,4,1 },
			{ 5,1,2 },
			{ 5,2,3 },
			{ 5,3,4 },
			{ 5,4,1 }
		};
		return edges;
	}

}

auto main() -> int{
	// 初期化
	if (glfwInit() == GL_FALSE)
	{
		std::cerr << "can`t initialize GLFW." << std::endl;
		return 1;
	}
	// 終了処理
	atexit(glfwTerminate);

	//　ウィンドウ作成
	get_window();

	//背景色
	glClearColor(1, 1, 1, 0);

	glm::mat4 mat1 = glm::perspective(glm::pi<float>() * 0.2f, 1.0f, 0.1f, 100.0f);
	glm::mat4 mat2 = glm::lookAt(glm::vec3(2.0f, 3.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 proj_mat = mat1 * mat2;

	std::unique_ptr<const Shape> sphere(new Sphere(static_cast<GLsizei>(get_vertices().size()), get_vertices().data(), static_cast<GLsizei>(get_edges().size()), get_edges().data(), proj_mat));

	glLineWidth(1.5);

	while (get_window())
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		sphere->draw();

		get_window().swapBuffers();
	}

	return 0;
}