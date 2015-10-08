#pragma once
#include <iostream>
#include <C:\Users\james\Documents\GitHub\332RayTracer\glm-0.9.6.3\glm\glm.hpp>

class Ray
{
private:
	float PixelNormalized(int val,int secondVal);
public:
	glm::vec3 Origin;
	glm::vec3 Direction;
	Ray::Ray();
	int width = 640;
	int height = 480;
	void RayCast(glm::vec3**);
	
};
