#include "Sphere.h"
#include <iostream>
//-1 means not collision
Intersect Sphere::Intersection(glm::vec3 ROrigin, glm::vec3 RDirection) {
	glm::vec3 l = Origin - ROrigin;
	float tca = glm::dot(l, RDirection);
	if (tca < 0) {
		//std::cout << "tca" << std::endl;
		return Intersect(-1,glm::vec3(0,0,0) );
	}
	float SS = dot(l, l) - pow(tca, 2);
	if (SS > pow(Radius, 2)) {
		//std::cout << "SS" << std::endl;
		return Intersect(-1, glm::vec3(0,0,0));
	}
	float t = (tca - sqrt(pow(Radius, 2) - SS));
	glm::vec3 ContactPoint = ROrigin + t*RDirection;
	glm::vec3 n = glm::normalize(Origin - ContactPoint);
	return Intersect(t,n);
}

glm::vec3 Sphere::PhongShading(float _t, glm::vec3 ROrigin, glm::vec3 RDirection, glm::vec3 CameraPos)
{
	glm::vec3 ContactPoint = ROrigin + _t*RDirection;
	glm::vec3 l = glm::normalize(ContactPoint - light->Position);
	glm::vec3 n = glm::normalize(Origin - ContactPoint);
	return CalcAmbient()+ CalcDiffuse(l, n) + CalcSpecular(l,n,CameraPos,ContactPoint);
}



