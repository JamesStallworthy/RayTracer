#include "Ray.h"
#include <math.h>
Ray::Ray(float _Fov, int _ScreenWidth, int _ScreenHeight,Light* _light, int _Amount) {
	Origin = glm::vec3(0,0,0);
	width = _ScreenWidth;
	height = _ScreenHeight;
	ImageAspectRatio = float(width) / float(height);
	Fov = tan((_Fov * 3.14 / 180) / 2);
	light = _light;
	AmountOfShapes = _Amount;
}

float Ray::PixelNormalized(int val,int secondVal)
{
	return ((float)val + 0.5)/secondVal;
}

Intersect Ray::CheckHit(Shape* SArray[], glm::vec3 _O, glm::vec3 _D)
{
	Intersect TempInt(0, glm::vec3(0, 0, 0));
	Intersect LowestIntersect(99, glm::vec3(0, 0, 0));
	for (int i = 0; i < AmountOfShapes; i++) {
		TempInt = SArray[i]->Intersection(_O, _D);
		if (TempInt.Distance != -1 && TempInt.Distance < LowestIntersect.Distance) {
			LowestIntersect = TempInt;
			LowestIntersect.ObjectID = i;
		}
	}
	return LowestIntersect;
}

void Ray::RayCast(glm::vec3** img, Shape* ShapeArray[])
{
	//SDL Clear Window

	SDL_FillRect(surface, NULL, 0x000000);
	//Saves the calculated pixel colour
	glm::vec3 ReturnedColour;

	float RemappedX;//Normalised x of pixel
	float RemappedY;//Normalised y of pixel
	float WorldSpacex;
	float WorldSpacey;
	glm::vec3 Pcameraspace; 

	//Saves the intersection values for raycast
	Intersect intersection(0,glm::vec3(0,0,0));
	
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			RemappedX = ((2*PixelNormalized(x,width) - 1)*ImageAspectRatio);
			RemappedY = (1 -2*PixelNormalized(y,height));
			WorldSpacex = RemappedX * Fov;
			WorldSpacey = RemappedY * Fov;
			Pcameraspace = glm::vec3(WorldSpacex + Origin.x, WorldSpacey + Origin.y,-1 + Origin.z);
			Direction = glm::normalize(Pcameraspace - Origin);

			//Gets intersection
			intersection = CheckHit(ShapeArray,Origin, Direction);
			//Checks if hits, then checks for hardshadows
			if (intersection.ObjectID != -1) {
				if (!HardShadows(ShapeArray, intersection)) {
					ReturnedColour = (ShapeArray[intersection.ObjectID]->PhongShading(intersection.Distance, Origin, Direction, Origin));
				}
				else {
					ReturnedColour = ShapeArray[intersection.ObjectID]->CalcAmbient();
				}
				//Draw to image array and then draw to screen
				img[x][y] = ReturnedColour;
				DrawToScreen(ReturnedColour, x, y);
			}
		}

	}//std::cout << WorldSpaceX << std::endl;
	SDL_UpdateWindowSurface(window);
}

bool Ray::HardShadows(Shape* _ShapeArray[], Intersect i)
{
	glm::vec3 ContactPoint = Origin+ i.Distance*Direction;
	glm::vec3 VecToLight = glm::normalize(light->Position - ContactPoint);

	//Intesection
	Intersect intersect = CheckHit(_ShapeArray, ContactPoint + i.Normal*0.001f, VecToLight);
	if (intersect.ObjectID == -1 || intersect.ObjectID == i.ObjectID)
		return false;
	else
		return true;
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




