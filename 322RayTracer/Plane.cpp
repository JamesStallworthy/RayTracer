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
	glm::vec3 ContactPoint = ROrigin + _t*RDirection;
	glm::vec3 l = glm::normalize(ContactPoint - light->Position);
	return CalcAmbient() + CalcDiffuse(l, Normal) + CalcSpecular(l, Normal, CameraPos, ContactPoint);
}

glm::vec3 Plane::CalcAmbient()
{
	return Colour*Ambient;
}

glm::vec3 Plane::CalcDiffuse(glm::vec3 l, glm::vec3 n)
{
	float Calc = (light->Intensity*std::fmax(0, glm::dot(l, n)));
	return Colour*Calc;
}

glm::vec3 Plane::CalcSpecular(glm::vec3 l, glm::vec3 n, glm::vec3 CameraPos, glm::vec3 ContactPoint) {
	glm::vec3 v = glm::normalize(CameraPos - ContactPoint);
	glm::vec3 r = glm::normalize(-2 * (glm::dot(l, n))*n + l);
	glm::vec3 Calc1 = Colour * light->Intensity;
	float Calc2 = pow(std::fmax(0, glm::dot(r, v)), 10);
	return Calc1*Calc2;
}