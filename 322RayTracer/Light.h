#pragma once
#include <iostream>
#include <glm.hpp>

class Light 
{
public:
	float Intensity;
	glm::vec3 Position;
	Light(glm::vec3 _Position, float _Intensity) :
		Intensity(_Intensity), Position(_Position) {};
};