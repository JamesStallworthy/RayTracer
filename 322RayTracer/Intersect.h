#pragma once
#include <iostream>
#include <glm.hpp>

class Intersect{
public:
	glm::vec3 Normal;
	float Distance;
	int ObjectID;
	Intersect(float _Distance, glm::vec3 _Normal) :
		Normal(_Normal), Distance(_Distance) {
		ObjectID = -1;
	};
};