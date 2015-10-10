#include <iostream>
#include "Shape.h"

glm::vec3 Shape::CalcAmbient()
{
	return Colour*Ambient;
}

glm::vec3 Shape::CalcDiffuse(glm::vec3 l, glm::vec3 n)
{
	float Calc = (light->Intensity*std::fmax(0, glm::dot(l, n)));
	return Colour*Calc;
}

glm::vec3 Shape::CalcSpecular(glm::vec3 l, glm::vec3 n, glm::vec3 CameraPos, glm::vec3 ContactPoint) {
	glm::vec3 v = glm::normalize(CameraPos - ContactPoint);
	glm::vec3 r = glm::normalize(-2 * (glm::dot(l, n))*n + l);
	glm::vec3 Calc1 = Colour * light->Intensity;
	float Calc2 = pow(std::fmax(0, glm::dot(r, v)), Specular);
	return Calc1*Calc2;
}

