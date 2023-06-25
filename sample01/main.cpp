#include <cstdlib>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h> 
#include <GL/glut.h>
#include <vector>
#include <fstream>
#include <memory>
#include "Window.h"
#include "ShaderProgram.h"

#define _USE_MATH_DEFINES
#include <math.h>

#include "Sphere.h"

namespace
{

	const std::vector<Sphere::Vertex>& get_vertex()
	{
		static std::vector<Sphere::Vertex> vertices;

		vertices.push_back({ {0,0,1}, {1,0,0} });
		vertices.push_back({ {1,0,0}, {0.5,1.0 ,0.5} });
		vertices.push_back({ {0,1,0}, {0.5,1.0 ,0.5} });
		vertices.push_back({ {-1,0,0}, {0.5,1.0 ,0.5} });
		vertices.push_back({ {0,-1,0}, {0.5,1.0 ,0.5} });
		vertices.push_back({ {0,0,-1}, {0, 0 ,1} });
		return vertices;
	}

	void lookAt(float ex, float ey, float ez,
		float tx, float ty, float tz,
		float ux, float uy, float uz,
		GLfloat* matrix)
	{
		float l;

		tx = ex - tx;
		ty = ey - ty;
		tz = ez - tz;
		l = sqrtf(tx * tx + ty * ty + tz * tz); /* この l と, */
		matrix[2] = tx / l;
		matrix[6] = ty / l;
		matrix[10] = tz / l;

		/* x 軸 = u x z 軸 */
		tx = uy * matrix[10] - uz * matrix[6];
		ty = uz * matrix[2] - ux * matrix[10];
		tz = ux * matrix[6] - uy * matrix[2];
		l = sqrtf(tx * tx + ty * ty + tz * tz); /* この l. */
		matrix[0] = tx / l;
		matrix[4] = ty / l;
		matrix[8] = tz / l;

		/* y 軸 = z 軸 x x 軸 */
		matrix[1] = matrix[6] * matrix[8] - matrix[10] * matrix[4];
		matrix[5] = matrix[10] * matrix[0] - matrix[2] * matrix[8];
		matrix[9] = matrix[2] * matrix[4] - matrix[6] * matrix[0];

		/* 平行移動 */
		matrix[12] = -(ex * matrix[0] + ey * matrix[4] + ez * matrix[8]);
		matrix[13] = -(ex * matrix[1] + ey * matrix[5] + ez * matrix[9]);
		matrix[14] = -(ex * matrix[2] + ey * matrix[6] + ez * matrix[10]);

		/* 残り */
		matrix[3] = matrix[7] = matrix[11] = 0.0f;
		matrix[15] = 1.0f;
	}
	void multiplyMatrix(const GLfloat* m0, const GLfloat* m1, GLfloat* matrix)
	{
		for (int i = 0; i < 16; ++i) {
			int j = i & ~3, k = i & 3;

			matrix[i] = m0[j + 0] * m1[0 + k]
				+ m0[j + 1] * m1[4 + k]
				+ m0[j + 2] * m1[8 + k]
				+ m0[j + 3] * m1[12 + k];
		}
	}

	void perspectiveMatrix(float left, float right,
		float bottom, float top,
		float _near, float _far,
		GLfloat* matrix)
	{
		float dx = right - left;
		float dy = top - bottom;
		float dz = _far - _near;

		matrix[0] = 2.0f * _near / dx;
		matrix[5] = 2.0f * _near / dy;
		matrix[8] = (right + left) / dx;
		matrix[9] = (top + bottom) / dy;
		matrix[10] = -(_far + _near) / dz;
		matrix[11] = -1.0f;
		matrix[14] = -2.0f * _far * _near / dz;
		matrix[1] = matrix[2] = matrix[3] = matrix[4] =
			matrix[6] = matrix[7] = matrix[12] = matrix[13] = matrix[15] = 0.0f;
	}
}

int main() {
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

	std::vector<Sphere::Vertex> vertices;
	vertices.push_back({ {0,0,1}, {1,0,0} });
	vertices.push_back({ {1,0,0}, {0.5,1.0 ,0.5} });
	vertices.push_back({ {0,1,0}, {0.5,1.0 ,0.5} });
	vertices.push_back({ {-1,0,0}, {0.5,1.0 ,0.5} });
	vertices.push_back({ {0,-1,0}, {0.5,1.0 ,0.5} });
	vertices.push_back({ {0,0,-1}, {0, 0 ,1} });

	std::vector<Sphere::Edge> edges;
	edges.push_back({ 0,1 });
	edges.push_back({ 0,2 });
	edges.push_back({ 0,3 });
	edges.push_back({ 0,4 });
	edges.push_back({ 1,2 });
	edges.push_back({ 2,3 });
	edges.push_back({ 3,4 });
	edges.push_back({ 4,1 });
	edges.push_back({ 1,5 });
	edges.push_back({ 2,5 });
	edges.push_back({ 3,5 });
	edges.push_back({ 4,5 });

	glm::mat4 mat1;
	perspectiveMatrix(-1.0f , 1.0f, -1.0f, 1.0f , 7.0f, 20.0f, &(mat1[0][0]));
	glm::mat4 mat2;
	lookAt(5.0f, 7.0f, 6.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, &(mat2[0][0])); 
	glm::mat4 proj_mat = mat1 * mat2;

	std::unique_ptr<const Shape> sphere(new Sphere(vertices.size(), vertices.data(), edges.size(), edges.data(), proj_mat));

	while (window)
	{
		glClear(GL_COLOR_BUFFER_BIT);

		sphere->draw();

		window.swapBuffers();
	}

	return 0;
}