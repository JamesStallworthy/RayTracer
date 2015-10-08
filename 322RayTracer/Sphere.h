#pragma once
#include <D:\james\Documents\Visual Studio 2015\Projects\332RayTracer\glm-0.9.6.3\glm\glm.hpp>

class Sphere {
private:
public:
	glm::vec3 Origin;
	float Radius;
	glm::vec3 Colour;
	Sphere();
	Sphere(glm::vec3, float, glm::vec3);
	bool RaySphere(glm::vec3 Origin, glm::vec3 Direction);
};