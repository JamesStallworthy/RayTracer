#pragma once
#include <glm.hpp>
#include "Shape.h"

class Sphere :public Shape {
private:
public:
	glm::vec3 Origin;
	float Radius;
	Sphere(glm::vec3 o, float r, glm::vec3 c) :
		Shape(c), Origin(o), Radius(r)
	{
	};
	virtual float Intersection(glm::vec3 Origin, glm::vec3 Direction);
	
};