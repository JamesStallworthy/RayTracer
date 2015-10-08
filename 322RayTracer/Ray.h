#pragma once
#include <C:\Users\james\Documents\GitHub\332RayTracer\glm-0.9.6.3\glm\glm.hpp>

class Ray
{
public:
	glm::vec3 Origin;
	glm::vec3 Direction;
	int width = 640;
	int height = 480;
	void RayCast();
	void GetWorldX();
	void GetWorldY();
};
