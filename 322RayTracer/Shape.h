#pragma once
#include <iostream>
#include <glm.hpp>

class Shape
{
public:
	Shape(glm::vec3 _Colour,float _Ambient, float _Specular) :
		Colour(_Colour),Ambient(_Ambient), Specular(_Specular){};
	glm::vec3 Colour;
	float Ambient;
	float Specular;
	virtual float Intersection(glm::vec3 Origin, glm::vec3 Direction)=0;
	virtual glm::vec3 PhongShading(float, glm::vec3, glm::vec3, glm::vec3) = 0;
};