#pragma once
#include "glm.hpp"

class AreaLight {
public:
	glm::vec3 position;
	float radius;
	float intensity;
	int samples;
	AreaLight(glm::vec3 _position, float _radius, float _intensity,int _samples) :
		position(_position), radius(_radius), intensity(_intensity),samples(_samples)  {};
};