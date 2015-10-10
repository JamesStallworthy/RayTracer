#pragma once
#include <iostream>
#include "Shape.h"
#include <glm.hpp>

class Triangle : public Shape
{
public:
	glm::vec3 Normal;
	glm::vec3 a;
	glm::vec3 b;
	glm::vec3 c;
	void CalculateNormal();
	Triangle(glm::vec3 Point1, glm::vec3 Point2, glm::vec3 Point3, glm::vec3 c, float _Ambient) :
		Shape(c,_Ambient), a(Point1), b(Point2), c(Point3)
	{
		CalculateNormal();
	};
	virtual float Intersection(glm::vec3 Origin, glm::vec3 Direction);
	virtual glm::vec3 PhongShading(float, glm::vec3, glm::vec3);
	glm::vec3 CalcAmbient();
};
