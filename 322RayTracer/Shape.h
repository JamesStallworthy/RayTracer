#pragma once
#include <iostream>
#include <glm.hpp>

class Shape
{
public:
	Shape(glm::vec3 _Colour) :
		Colour(_Colour){};
	glm::vec3 Colour;
	virtual float Intersection(glm::vec3 Origin, glm::vec3 Direction)=0;
};