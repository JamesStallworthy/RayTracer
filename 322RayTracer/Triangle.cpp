#include "Triangle.h"

void Triangle::CalculateNormal()
{
	glm::vec3 v1 = b - a;
	glm::vec3 v2 = c - a;
	Normal = glm::normalize(glm::cross(v1, v2));
	std::cout << Normal.y << std::endl;

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

glm::vec3 Triangle::PhongShading(float _t, glm::vec3 ROrigin, glm::vec3 RDirection)
{
	return CalcAmbient();;
}

glm::vec3 Triangle::CalcAmbient()
{
	return Colour*Ambient;
}