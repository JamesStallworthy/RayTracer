#include "Sphere.h"
#include <iostream>
//-1 means not collision
float Sphere::Intersection(glm::vec3 ROrigin, glm::vec3 RDirection) {
	glm::vec3 l = Origin - ROrigin;
	float tca = glm::dot(l, RDirection);
	if (tca < 0) {
		std::cout << "tca" << std::endl;
		return -1;
	}
	float SS = dot(l, l) - pow(tca, 2);
	if (SS > pow(Radius, 2)) {
		//std::cout << "SS" << std::endl;
		return -1;
	}
	return (tca-sqrt(pow(Radius,2) - SS));
}

glm::vec3 Sphere::PhongShading(float _t, glm::vec3 ROrigin, glm::vec3 RDirection)
{
	CalcDiffuse(_t);
	return CalcAmbient();;
}

glm::vec3 Sphere::CalcAmbient()
{
	return Colour*Ambient;
}

glm::vec3 Sphere::CalcDiffuse(float t) 
{
	glm::vec3 ContactPoint;
	glm::vec3 l;
	(light->Intensity*std::fmax(0, 1));
	return Colour;
}

