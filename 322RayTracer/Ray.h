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
	float Fov;
public:
	glm::vec3 Origin;
	glm::vec3 Direction;
	Ray::Ray(float);
	int width = 640;
	int height = 480;
	void RayCast(glm::vec3**, Shape*[],int Amount);
};
