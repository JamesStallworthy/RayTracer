#include "Poly.h"

void Poly::CalcNormal()
{
	glm::vec3 v1 = B - A;
	glm::vec3 v2 = C - A;
	Normal = glm::normalize(glm::cross(v1, v2));
}

Intersect Poly::Intersection(glm::vec3 ROrigin, glm::vec3 RDirection)
{
	//Plane intersection equal to the plane the triangle is on
	glm::vec3 p;
	float denominator = glm::dot(RDirection, Normal);
	if (abs(denominator) > 0.000001) {
		float t = glm::dot((A - ROrigin), Normal) / denominator;
		//FIRST TRIANGLE

		p = ROrigin + t*RDirection;
		float Areaw = glm::dot(Normal, glm::cross((B - A), (C - A)));
		float Areau = glm::dot(Normal, glm::cross((B - p), (C - p)));
		float Areav = glm::dot(Normal, glm::cross((C - p), (A - p)));

		float u = Areau / Areaw;
		float v = Areav / Areaw;
		float w = 1 - u - v;
		//checking if p is inside triangle
		if ((u > 0 && u <1) && (v > 0 && v <1) && (w > 0 && w <1)) {
			return Intersect(t, Normal);
		}
		

		//SECOND TRIANGLE

		p = ROrigin + t*RDirection;
		Areaw = glm::dot(Normal, glm::cross((C - B), (D - B)));
		Areau = glm::dot(Normal, glm::cross((C - p), (D - p)));
		Areav = glm::dot(Normal, glm::cross((D - p), (B - p)));

		u = Areau / Areaw;
		v = Areav / Areaw;

		//checking if p is inside triangle
		if (u < 0 || u > 1) {
			return Intersect(-1, Normal);
		}
		if (v < 0 || (u + v)>1)
			return Intersect(-1, Normal);
		else {
			return Intersect(t, Normal);
		}
	}
	return Intersect(-1, Normal);
}

glm::vec3 Poly::PhongShading(float _t, glm::vec3 ROrigin, glm::vec3 RDirection)
{
	glm::vec3 ContactPoint = ROrigin + _t*RDirection;
	glm::vec3 l = glm::normalize(ContactPoint - light->Position);
	return CalcAmbient() + CalcDiffuse(l, Normal) + CalcSpecular(l, Normal, ROrigin, ContactPoint);
}
