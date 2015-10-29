#pragma once
#include "Shape.h"

class Poly : public Shape {
private:
	void CalcNormal();
public:
	glm::vec3 Normal;
	//Coords of corners;
	glm::vec3 A;
	glm::vec3 B;
	glm::vec3 C;
	glm::vec3 D;
	Poly(glm::vec3 _A, glm::vec3 _B, glm::vec3 _C, glm::vec3 _D, glm::vec3 _Colour, float _Ambient, float _Specular, bool _Reflective, float _Reflectivity, float _AmountOfBaseColour) :
		Shape(_Colour, _Ambient, _Specular,_Reflective, _Reflectivity, _AmountOfBaseColour), A(_A), B(_B), C(_C), D(_D) {
		CalcNormal();

	};
	virtual Intersect Intersection(glm::vec3 Origin, glm::vec3 Direction);
	virtual glm::vec3 PhongShading(float, glm::vec3, glm::vec3, glm::vec3, float, Shape*[], int numberofshapes);

};