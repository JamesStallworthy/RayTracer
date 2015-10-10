#pragma once
#include <iostream>
#include <glm.hpp>

class Shape
{
public:
	Shape(glm::vec3 _Colour,float _Ambient) :
		Colour(_Colour),Ambient(_Ambient){};
	glm::vec3 Colour;
	float Ambient;
	virtual float Intersection(glm::vec3 Origin, glm::vec3 Direction)=0;
	virtual glm::vec3 PhongShading(float, glm::vec3, glm::vec3, glm::vec3) = 0;
};