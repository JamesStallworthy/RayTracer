#include "Triangle.h"

void Triangle::CalculateNormal()
{
	glm::vec3 v1 = b - a;
	glm::vec3 v2 = c - a;
	Normal = glm::normalize(glm::cross(v2, v1));
	

}

float Triangle::Intersection(glm::vec3 ROrigin, glm::vec3 RDirection)
{
	//Plane intersection equal to the plane the triangle is on
	glm::vec3 p;
	float denominator = glm::dot(RDirection, Normal);
	if (abs(denominator) > 0.000001) {
		float t = glm::dot((a - ROrigin), Normal) / denominator;
		if (t >= 0) {
			//http://gamedev.stackexchange.com/questions/23743/whats-the-most-efficient-way-to-find-barycentric-coordinates
			p = ROrigin + t*RDirection;
			float Areaw = glm::dot(Normal, glm::cross((b - a), (c - a)));
			float Areau = glm::dot(Normal, glm::cross((b - p), (c - p)));
			float Areav = glm::dot(Normal, glm::cross((c - p), (a - p)));

			float u = Areau / Areaw;
			float v = Areav / Areaw;

			//checking if p is inside triangle
			if (u < 0 || u > 1) {
				return -1;
			}
			if (v < 0 || (u + v)>1)
				return -1;
			else {
				return t;
			}
		}
	}

	return -1;
}

glm::vec3 Triangle::PhongShading(float _t, glm::vec3 ROrigin, glm::vec3 RDirection, glm::vec3 CameraPos)
{
	glm::vec3 ContactPoint = ROrigin + _t*RDirection;
	glm::vec3 l = glm::normalize(ContactPoint - light->Position);
	return CalcAmbient() + CalcDiffuse(l, Normal) + CalcSpecular(l,Normal,CameraPos,ContactPoint);
}

glm::vec3 Triangle::CalcAmbient()
{
	return Colour*Ambient;
}

glm::vec3 Triangle::CalcDiffuse(glm::vec3 l, glm::vec3 n)
{
	float Calc = (light->Intensity*std::fmax(0, glm::dot(l, n)));
	return Colour*Calc;
}

glm::vec3 Triangle::CalcSpecular(glm::vec3 l, glm::vec3 n, glm::vec3 CameraPos, glm::vec3 ContactPoint) {
	glm::vec3 v = glm::normalize(CameraPos - ContactPoint);
	glm::vec3 r = glm::normalize(-2 * (glm::dot(l, n))*n + l);
	glm::vec3 Calc1 = Colour * light->Intensity;
	float Calc2 = pow(std::fmax(0, glm::dot(r, v)), 10);
	return Calc1*Calc2;
}
