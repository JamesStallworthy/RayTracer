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

glm::vec3 Sphere::PhongShading(float _t, glm::vec3 ROrigin, glm::vec3 RDirection, glm::vec3 CameraPos)
{
	glm::vec3 ContactPoint = ROrigin + _t*RDirection;
	glm::vec3 l = glm::normalize(ContactPoint - light->Position);
	glm::vec3 n = glm::normalize(Origin - ContactPoint);
	return CalcAmbient()+ CalcDiffuse(l, n) + CalcSpecular(l,n,CameraPos,ContactPoint);
}

glm::vec3 Sphere::CalcAmbient()
{
	return Colour*Ambient;
}

glm::vec3 Sphere::CalcDiffuse(glm::vec3 l, glm::vec3 n) 
{
	float Calc = (light->Intensity*std::fmax(0, glm::dot(l, n)));
	return Colour*Calc;
}

glm::vec3 Sphere::CalcSpecular(glm::vec3 l, glm::vec3 n, glm::vec3 CameraPos, glm::vec3 ContactPoint) {
	glm::vec3 v = glm::normalize(CameraPos- ContactPoint);
	glm::vec3 r = glm::normalize(-2 * (glm::dot(l,n))*n + l);
	glm::vec3 Calc1 = Colour * light->Intensity ;
	float Calc2 = pow(std::fmax(0, glm::dot(r,v)),10);
	return Calc1*Calc2;
}

