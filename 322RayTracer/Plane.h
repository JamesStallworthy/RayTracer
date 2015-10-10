#pragma once
#include "Shape.h"

class Plane : public Shape {
public:
	glm::vec3 Origin;
	glm::vec3 Normal;
	Plane(glm::vec3 o, glm::vec3 n, glm::vec3 c, float _Ambient) :
		Shape(c,_Ambient), Origin(o)
	{
		Normal = glm::normalize(n);
	};

	virtual float Intersection(glm::vec3 Origin, glm::vec3 Direction);
	virtual glm::vec3 PhongShading();
	glm::vec3 CalcAmbient();
};