#include "Plane.h"
#include "math.h"

float Plane::Intersection(glm::vec3 ROrigin, glm::vec3 RDirection)
{
	float denominator = glm::dot(RDirection, Normal);
	if (abs(denominator) > 0.000001) {
		float t = glm::dot((Origin - ROrigin), Normal) / denominator;
		if (t >= 0) return t;
	}

	return -1;
}

glm::vec3 Plane::PhongShading(float _t, glm::vec3 ROrigin, glm::vec3 RDirection, glm::vec3 CameraPos)
{
	return CalcAmbient();;
}

glm::vec3 Plane::CalcAmbient()
{
	return Colour*Ambient;
}
