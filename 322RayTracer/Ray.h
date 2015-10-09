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
public:
	glm::vec3 Origin;
	glm::vec3 Direction;
	Ray::Ray();
	int width = 640;
	int height = 480;
	void RayCast(glm::vec3**, Shape*[],int Amount);
};
