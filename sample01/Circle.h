#pragma once
#include <array>
#include "Shape.h"
#include "ShaderProgram.h"
#include "Drawer.h"

class Circle : public Shape
{
	Vector center;
	float radius;

	
public:
	Circle() : center(), radius(){}

	void draw() const override
	{

	}
};

