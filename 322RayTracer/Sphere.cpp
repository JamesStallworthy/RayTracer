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
	
	return CalcAmbient()+ CalcDiffuse(_t, ROrigin, RDirection);;
}

glm::vec3 Sphere::CalcAmbient()
{
	return Colour*Ambient;
}

glm::vec3 Sphere::CalcDiffuse(float t,glm::vec3 ROrigin, glm::vec3 RDirection) 
{
	glm::vec3 ContactPoint = ROrigin + t*RDirection;
	glm::vec3 l = ContactPoint - light->Position;
	glm::vec3 n = Origin - ContactPoint;
	float Calc = (light->Intensity*std::fmax(0, glm::dot(glm::normalize(l), glm::normalize(n))));
	return Colour*Calc;
}

