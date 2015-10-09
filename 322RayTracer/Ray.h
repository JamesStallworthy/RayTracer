#pragma once
#include <iostream>
#include <glm.hpp>
#include "Sphere.h"

class Ray
{
private:
	float PixelNormalized(int val,int secondVal);
	float ImageAspectRatio;
	float CheckHit(Shape* s);
public:
	glm::vec3 Origin;
	glm::vec3 Direction;
	Ray::Ray();
	int width = 640;
	int height = 480;
	void RayCast(glm::vec3**, Shape*[]);
};
