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
	bool Reflective;
	Shape(glm::vec3 _Colour, float _Ambient, float _Specular, bool _Reflective) :
		Colour(_Colour), Ambient(_Ambient), Specular(_Specular),  Reflective(_Reflective){};
	glm::vec3 Colour;
	
	virtual Intersect Intersection(glm::vec3 Origin, glm::vec3 Direction)=0;
	virtual glm::vec3 PhongShading(float, glm::vec3, glm::vec3, glm::vec3, float, Shape*[], int numberofshapes) = 0;
	glm::vec3 CalcAmbient();
	glm::vec3 CalcDiffuse(glm::vec3 l, glm::vec3 n, float intensity);
	glm::vec3 CalcSpecular(glm::vec3 l, glm::vec3 n, glm::vec3 CameraPos, glm::vec3 ContactPoint, float);
	Intersect CheckHit(Shape * SArray[], glm::vec3 _O, glm::vec3 _D, float AmountOfShapes);
	glm::vec3 Reflections(glm::vec3 n,glm::vec3 RDireciton, glm::vec3 ContactPoint, Shape* ShapeArray[], glm::vec3 lightpos, float intensity, int numberofshapes);
};