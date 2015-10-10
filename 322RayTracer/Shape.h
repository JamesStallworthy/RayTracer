#pragma once
#include <iostream>
#include <glm.hpp>
#include "Light.h"

class Shape
{
public:
	float Ambient;
	float Specular;
	Light* light;
	Shape(glm::vec3 _Colour, float _Ambient, float _Specular, Light* _light) :
		Colour(_Colour), Ambient(_Ambient), Specular(_Specular), light(_light) {};
	glm::vec3 Colour;
	
	virtual float Intersection(glm::vec3 Origin, glm::vec3 Direction)=0;
	virtual glm::vec3 PhongShading(float, glm::vec3, glm::vec3, glm::vec3) = 0;
	glm::vec3 CalcAmbient();
	glm::vec3 CalcDiffuse(glm::vec3 l, glm::vec3 n);
	glm::vec3 CalcSpecular(glm::vec3 l, glm::vec3 n, glm::vec3 CameraPos, glm::vec3 ContactPoint);
};