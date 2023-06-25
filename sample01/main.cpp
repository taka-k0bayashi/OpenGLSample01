#include <cstdlib>
#include <iostream>
#include <vector>
#include <memory>
#include "Window.h"
#include "ShaderProgram.h"

#define _USE_MATH_DEFINES
#include <math.h>

#include "Sphere.h"

namespace
{
	void lookAt(float ex, float ey, float ez,
		        float tx, float ty, float tz,
		        float ux, float uy, float uz,
		        glm::mat4& matrix)
	{
		float l;

		tx = ex - tx;
		ty = ey - ty;
		tz = ez - tz;
		l = sqrtf(tx * tx + ty * ty + tz * tz);
		matrix[0][2] = tx / l;
		matrix[1][2] = ty / l;
		matrix[2][2] = tz / l;
		tx = uy * matrix[2][2] - uz * matrix[1][2];
		ty = uz * matrix[0][2] - ux * matrix[2][2];
		tz = ux * matrix[1][2] - uy * matrix[0][2];
		l = sqrtf(tx * tx + ty * ty + tz * tz);
		matrix[0][0] = tx / l;
		matrix[1][0] = ty / l;
		matrix[2][0] = tz / l;
		matrix[0][1] = matrix[1][2] * matrix[2][0] - matrix[2][2] * matrix[1][0];
		matrix[1][1] = matrix[2][2] * matrix[0][0] - matrix[0][2] * matrix[2][0];
		matrix[2][1] = matrix[0][2] * matrix[1][0] - matrix[1][2] * matrix[0][0];
		matrix[3][0] = -(ex * matrix[0][0] + ey * matrix[1][0] + ez * matrix[2][0]);
		matrix[3][1] = -(ex * matrix[0][1] + ey * matrix[1][1] + ez * matrix[2][1]);
		matrix[3][2] = -(ex * matrix[0][2] + ey * matrix[1][2] + ez * matrix[2][2]);
		matrix[0][3] = matrix[1][3] = matrix[2][3] = 0.0f;
		matrix[3][3] = 1.0f;
	}

	void perspectiveMatrix(float left, float right,
		                   float bottom, float top,
		                   float _near, float _far,
		                   glm::mat4& matrix)
	{
		float dx = right - left;
		float dy = top - bottom;
		float dz = _far - _near;

		matrix[0][0] = 2.0f * _near / dx;
		matrix[1][1] = 2.0f * _near / dy;
		matrix[2][0] = (right + left) / dx;
		matrix[2][1] = (top + bottom) / dy;
		matrix[2][2] = -(_far + _near) / dz;
		matrix[2][3] = -1.0f;
		matrix[3][2] = -2.0f * _far * _near / dz;
		matrix[0][1] = matrix[0][2] = matrix[0][3] = matrix[1][0] = matrix[1][2] = matrix[1][3] = matrix[3][0] = matrix[3][1] = matrix[3][3] = 0.0f;
	}

	const std::vector<Sphere::Vertex>& get_vertices()
	{
		static std::vector<Sphere::Vertex> vertices =
		{
			{ {0,0,1}, {1,0,0} },
			{ {1,0,0}, {0.5,1.0 ,0.5} },
			{ {0,1,0}, {0.5,1.0 ,0.5} },
			{ {-1,0,0}, {0.5,1.0 ,0.5} },
			{ {0,-1,0}, {0.5,1.0 ,0.5} },
			{ {0,0,-1}, {0, 0 ,1} }
		};
		return vertices;
	}

	const std::vector<Sphere::Edge>& get_edges()
	{
		static std::vector<Sphere::Edge> edges =
		{
			{ 0,1 },
			{ 0,2 },
			{ 0,3 },
			{ 0,4 },
			{ 1,2 },
			{ 2,3 },
			{ 3,4 },
			{ 4,1 },
			{ 1,5 },
			{ 2,5 },
			{ 3,5 },
			{ 4,5 }
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
	Window window(1280, 960);

	//背景色
	glClearColor(1, 1, 1, 0);

	glm::mat4 mat1;
	perspectiveMatrix(-1.0f , 1.0f, -1.0f, 1.0f , 7.0f, 20.0f, mat1);
	glm::mat4 mat2;
	lookAt(5.0f, 7.0f, 5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, mat2); 
	glm::mat4 proj_mat = mat1 * mat2;

	std::unique_ptr<const Shape> sphere(new Sphere(static_cast<GLsizei>(get_vertices().size()), get_vertices().data(), static_cast<GLsizei>(get_edges().size()), get_edges().data(), proj_mat));

	while (window)
	{
		glClear(GL_COLOR_BUFFER_BIT);

		sphere->draw();

		window.swapBuffers();
	}

	return 0;
}