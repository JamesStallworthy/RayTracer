#pragma once
#include "Shape.h"
#include "light.h"

class Plane : public Shape {
public:
	glm::vec3 Origin;
	glm::vec3 Normal;
	//Light* light;
	Plane(glm::vec3 o, glm::vec3 n, glm::vec3 c, float _Ambient,float _Specular, bool _Reflective, float _Reflectivity, float _AmountOfBaseColour) :
		Shape(c,_Ambient,_Specular, _Reflective, _Reflectivity, _AmountOfBaseColour), Origin(o)
	{
		Normal = glm::normalize(n);
	};

	virtual Intersect Intersection(glm::vec3 Origin, glm::vec3 Direction);
	virtual glm::vec3 PhongShading(float, glm::vec3, glm::vec3, glm::vec3, float, Shape*[], int numberofshapes);
};