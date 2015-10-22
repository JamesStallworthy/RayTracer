#pragma once
#include <iostream>
#include <glm.hpp>
#include "Sphere.h"
#include <vector>
#include "light.h"
#include "AreaLight.h"
#include <SDL.h>
#include <math.h>

class Ray
{
private:
	float PixelNormalized(int val,int secondVal);
	float ImageAspectRatio;
	Intersect CheckHit(Shape* s[],glm::vec3 _O,glm::vec3 _D);
	int AmountOfShapes;
	int width;
	int height;
	float Fov;
	float t;
	glm::vec3 Normal;
	Light* light;
	AreaLight* arealight;
	SDL_Window *window;
	SDL_Surface *surface;
	Uint32 PixelColour;
	SDL_Rect Pixel;
public:
	glm::vec3 Origin;
	glm::vec3 Direction;
	Ray::Ray(float, int, int, Light*, AreaLight*, int);
	void RayCast(glm::vec3**, Shape*[]);
	bool HardShadows(Shape*[], Intersect);
	float SoftShadows(Shape*[], Intersect);
	glm::vec3 RandomPointInAreaLight();
	void SetWindow(SDL_Window *_window, SDL_Surface *surface);
	void DrawToScreen(glm::vec3 _Colour, int x, int y);
};
