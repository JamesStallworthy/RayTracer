#pragma once
#include "Shape.h"
#include "light.h"

class Plane : public Shape {
public:
	glm::vec3 Origin;
	glm::vec3 Normal;
	//Light* light;
	Plane(glm::vec3 o, glm::vec3 n, glm::vec3 c, float _Ambient,float _Specular, Light* _light) :
		Shape(c,_Ambient,_Specular,_light), Origin(o)
	{
		Normal = glm::normalize(n);
	};

	virtual float Intersection(glm::vec3 Origin, glm::vec3 Direction);
	virtual glm::vec3 PhongShading(float, glm::vec3, glm::vec3, glm::vec3);
	/*glm::vec3 CalcAmbient();
	glm::vec3 CalcDiffuse(glm::vec3 l, glm::vec3 n);
	glm::vec3 CalcSpecular(glm::vec3 l, glm::vec3 n, glm::vec3 CameraPos, glm::vec3 ContactPoint);*/
};