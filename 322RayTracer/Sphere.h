#pragma once
#include <glm.hpp>
#include "Shape.h"
#include "Light.h"

class Sphere :public Shape {
private:
public:
	Light* light;
	glm::vec3 Origin;
	float Radius;
	Sphere(glm::vec3 o, float r, glm::vec3 c,float _Ambient,Light* _light) :
		Shape(c,_Ambient), Origin(o), Radius(r),light(_light)
	{
	};
	virtual float Intersection(glm::vec3 Origin, glm::vec3 Direction);
	virtual glm::vec3 PhongShading();
	glm::vec3 CalcAmbient();
	glm::vec3 CalcDiffuse();
};