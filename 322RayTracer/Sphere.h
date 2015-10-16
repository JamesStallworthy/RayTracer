#pragma once
#include <glm.hpp>
#include "Shape.h"
#include "Light.h"

class Sphere :public Shape {
private:
public:
	//Light* light;
	glm::vec3 Origin;
	float Radius;
	Sphere(glm::vec3 o, float r, glm::vec3 c,float _Ambient, float _Specular, Light* _light) :
		Shape(c,_Ambient,_Specular,_light), Origin(o), Radius(r)
	{
	};
	virtual Intersect Intersection(glm::vec3 Origin, glm::vec3 Direction);
	virtual glm::vec3 PhongShading(float, glm::vec3, glm::vec3);
	/*glm::vec3 CalcAmbient();
	glm::vec3 CalcDiffuse(glm::vec3, glm::vec3);
	glm::vec3 CalcSpecular(glm::vec3, glm::vec3, glm::vec3,glm::vec3);*/
};