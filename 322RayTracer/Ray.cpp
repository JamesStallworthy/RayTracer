#include "Ray.h"
#include <math.h>
Ray::Ray(float _Fov, int ScreenWidth, int ScreenHeight,Light* _light) {
	Origin = glm::vec3(0,0,0);
	width = ScreenWidth;
	height = ScreenHeight;
	ImageAspectRatio = float(width) / float(height);
	Fov = tan((_Fov * 3.14 / 180) / 2);
	light = _light;
}

float Ray::PixelNormalized(int val,int secondVal)
{
	return ((float)val + 0.5)/secondVal;
}

int Ray::CheckHit(Shape* s[], glm::vec3 _O, glm::vec3 _D)
{
	int LowestID=-1;
	float LowestValue=99;
	float temp;
	for (int i = 0; i < AmountOfShapes; i++) {
		temp=s[i]->Intersection(_O, _D);
		if (temp != -1 && temp < LowestValue) {
			LowestValue = temp;
			LowestID = i;
		}
	}
	t = LowestValue;
	return LowestID;
}


void Ray::RayCast(glm::vec3** img, Shape* ShapeArray[],int Amount)
{
	//SDL
	glm::vec3 ReturnedColour;

	AmountOfShapes = Amount;
	
	float RemappedX;//Normalised x of pixel
	float RemappedY;//Normalised y of pixel
	float WorldSpacex;
	float WorldSpacey;
	glm::vec3 Pcameraspace; 
	
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			RemappedX = ((2*PixelNormalized(x,width) - 1)*ImageAspectRatio);
			RemappedY = (1 -2*PixelNormalized(y,height));
			WorldSpacex = RemappedX * Fov;
			WorldSpacey = RemappedY * Fov;
			Pcameraspace = glm::vec3(WorldSpacex, WorldSpacey,-1);
			Direction = glm::normalize(Pcameraspace - Origin);
			int ShapeID = CheckHit(ShapeArray,Origin, Direction);
			if (ShapeID != -1) {
				ReturnedColour = (ShapeArray[ShapeID]->PhongShading(t, Origin, Direction, Origin)) *HardShadows(ShapeArray, ShapeID);
				img[x][y] = ReturnedColour;
				DrawToScreen(ReturnedColour, x,y);
			}
		}

	}//std::cout << WorldSpaceX << std::endl;
	SDL_UpdateWindowSurface(window);
}

float Ray::HardShadows(Shape* ShapeArray[], int CurrentShape)
{
	float newt = t - 0.1;
	glm::vec3 ContactPoint = (Origin) + t*Direction;
	glm::vec3 VecToLight = light->Position - ContactPoint ;
	int HitObject = CheckHit(ShapeArray, ContactPoint, VecToLight);
	if (HitObject == -1 ||HitObject == CurrentShape)
		return 1;
	else
		return 0.5;
}

void Ray::SetWindow(SDL_Window * _window, SDL_Surface * _surface)
{
	window = _window;
	surface = _surface;
}

void Ray::DrawToScreen(glm::vec3 _Colour, int x, int y)
{
	glm::vec3 Colour = _Colour*255.0f;
	if (Colour.x > 255)
		Colour.x = 255;
	if (Colour.y > 255)
		Colour.y = 255;
	if (Colour.z > 255)
		Colour.z = 255;
	PixelColour = SDL_MapRGB(surface->format, Colour.x, Colour.y, Colour.z);
	Pixel.x = x;
	Pixel.y = y;
	Pixel.w = 1;
	Pixel.h = 1;
	SDL_FillRect(surface, &Pixel, PixelColour);
}




