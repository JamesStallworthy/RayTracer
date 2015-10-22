#pragma once
#include "glm.hpp"

class AreaLight {
public:
	glm::vec3 position;
	float radius;
	float intensity;
	AreaLight(glm::vec3 _position, float _radius, float _intensity) :
		position(_position), radius(_radius), intensity(_intensity) {};
};