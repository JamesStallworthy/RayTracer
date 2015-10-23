#pragma once
#include <iostream>
#include <glm.hpp>
#include "Light.h"
#include "Intersect.h"

class Shape
{
public:
	float Ambient;
	float Specular;
	Shape(glm::vec3 _Colour, float _Ambient, float _Specular) :
		Colour(_Colour), Ambient(_Ambient), Specular(_Specular) {};
	glm::vec3 Colour;
	
	virtual Intersect Intersection(glm::vec3 Origin, glm::vec3 Direction)=0;
	virtual glm::vec3 PhongShading(float, glm::vec3, glm::vec3, glm::vec3, float) = 0;
	glm::vec3 CalcAmbient();
	glm::vec3 CalcDiffuse(glm::vec3 l, glm::vec3 n, float intensity);
	glm::vec3 CalcSpecular(glm::vec3 l, glm::vec3 n, glm::vec3 CameraPos, glm::vec3 ContactPoint, float);
};