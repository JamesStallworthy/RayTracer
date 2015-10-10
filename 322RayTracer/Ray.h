#pragma once
#include <iostream>
#include <glm.hpp>
#include "Sphere.h"
#include <vector>

class Ray
{
private:
	float PixelNormalized(int val,int secondVal);
	float ImageAspectRatio;
	int CheckHit(Shape* s[]);
	int AmountOfShapes;
	int width;
	int height;
	float Fov;
	float t;
public:
	glm::vec3 Origin;
	glm::vec3 Direction;
	Ray::Ray(float, int, int);
	void RayCast(glm::vec3**, Shape*[],int Amount);
};
