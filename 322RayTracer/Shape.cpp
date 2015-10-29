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

Intersect Shape::CheckHit(Shape* SArray[], glm::vec3 _O, glm::vec3 _D, float AmountOfShapes)
{
	Intersect TempInt(0, glm::vec3(0, 0, 0));
	Intersect LowestIntersect(99999, glm::vec3(0, 0, 0));
	for (int i = 0; i < AmountOfShapes; i++) {
		TempInt = SArray[i]->Intersection(_O, _D);
		if (TempInt.Distance != -1 && TempInt.Distance < LowestIntersect.Distance) {
			LowestIntersect = TempInt;
			LowestIntersect.ObjectID = i;
		}
	}
	return LowestIntersect;
}

glm::vec3 Shape::Reflections(glm::vec3 n, glm::vec3 RDireciton, glm::vec3 ContactPoint, Shape* ShapeArray[])
{
	//r = d?2(d?n)n
	glm::vec3 RRay = RDireciton - 2.0f*(glm::dot(RDireciton, n) * n);
	Intersect Object = CheckHit(ShapeArray, ContactPoint, RRay, 8);
	if (Object.ObjectID!=-1)
		return ShapeArray[Object.ObjectID]->PhongShading(Object.Distance, ContactPoint, RRay, glm::vec3(0,10,0), 1, ShapeArray);

	return glm::vec3(0, 0, 0);
}


