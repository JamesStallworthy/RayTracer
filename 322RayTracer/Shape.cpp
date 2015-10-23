#include <iostream>
#include "Shape.h"

glm::vec3 Shape::CalcAmbient()
{
	return Colour*Ambient;
}

glm::vec3 Shape::CalcDiffuse(glm::vec3 l, glm::vec3 n, float intensity)
{
	float Calc = (intensity*std::fmax(0, glm::dot(l, n)));
	return Colour*Calc;
}

glm::vec3 Shape::CalcSpecular(glm::vec3 l, glm::vec3 n, glm::vec3 CameraPos, glm::vec3 ContactPoint, float intensity) {
	glm::vec3 v = glm::normalize(CameraPos - ContactPoint);
	glm::vec3 r = glm::normalize(0.1f * (glm::dot(l, n))*n + l);
	glm::vec3 Calc1 = Colour * intensity;
	float Calc2 = pow(std::fmax(0, glm::dot(r, v)), Specular);
	return Calc1*Calc2;
}

