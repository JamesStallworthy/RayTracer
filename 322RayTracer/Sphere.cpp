#include "Sphere.h"

Sphere::Sphere(glm::vec3 o, float r, glm::vec3 c)
{
	Origin = o;
	Radius = r;
	Colour = c;
}

bool Sphere::RaySphere(glm::vec3 ROrigin, glm::vec3 RDirection)
{
	glm::vec3 l = Origin - ROrigin;
	float tca = glm::dot(l, RDirection);
	if (tca < 0)
		return false;
	float SS = dot(l, l) - tca;
	if (SS > pow(Radius, 2))
		return false;
	return true;
}


