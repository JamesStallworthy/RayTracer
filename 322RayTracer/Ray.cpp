#include "Ray.h"
#include <math.h>
Ray::Ray(float _Fov, int ScreenWidth, int ScreenHeight,Light* _light, AreaLight* _arealight, int _Amount) {
	Origin = glm::vec3(0,0,0);
	width = ScreenWidth;
	height = ScreenHeight;
	ImageAspectRatio = float(width) / float(height);
	Fov = tan((_Fov * 3.14 / 180) / 2);
	light = _light;
	arealight = _arealight;
	AmountOfShapes = _Amount;
}

float Ray::PixelNormalized(int val,int secondVal)
{
	return ((float)val + 0.5)/secondVal;
}

Intersect Ray::CheckHit(Shape* SArray[], glm::vec3 _O, glm::vec3 _D)
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


void Ray::RayCast(glm::vec3** img, Shape* ShapeArray[])
{
	//SDL clear screen
	SDL_FillRect(surface, NULL, 0x000000);
	//Pixel Colour
	glm::vec3 ReturnedColour;
	
	float RemappedX;//Normalised x of pixel
	float RemappedY;//Normalised y of pixel
	float WorldSpacex;
	float WorldSpacey;
	glm::vec3 Pcameraspace; 
	Intersect intersection(0,glm::vec3(0,0,0));
	
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			RemappedX = ((2*PixelNormalized(x,width) - 1)*ImageAspectRatio);
			RemappedY = (1 -2*PixelNormalized(y,height));
			WorldSpacex = RemappedX * Fov;
			WorldSpacey = RemappedY * Fov;
			Pcameraspace = glm::vec3(WorldSpacex+ Origin.x, WorldSpacey + Origin.y,-1+Origin.z);
			Direction = glm::normalize(Pcameraspace - Origin);

			intersection = CheckHit(ShapeArray,Origin, Direction);
			if (intersection.ObjectID != -1) {
				if (light != NULL) {
					//HARD SHADOWS
					std::cout << "Hard Shadows" << std::endl;
					if (!HardShadows(ShapeArray, intersection))
						ReturnedColour = (ShapeArray[intersection.ObjectID]->PhongShading(intersection.Distance, Origin, Direction));
					else
						ReturnedColour = ShapeArray[intersection.ObjectID]->CalcAmbient();
				}
				else {
					//SOFT SHADOWS
					float AverageSoftShadow = SoftShadows(ShapeArray, intersection);
					if (AverageSoftShadow == 0) {
						ReturnedColour = (ShapeArray[intersection.ObjectID]->PhongShading(intersection.Distance, Origin, Direction));
					}
					else {
						ReturnedColour = (ShapeArray[intersection.ObjectID]->PhongShading(intersection.Distance, Origin, Direction)) * (1 - AverageSoftShadow);
						//ReturnedColour = ShapeArray[intersection.ObjectID]->Colour * (1 -AverageSoftShadow);
					}

				}
				img[x][y] = ReturnedColour;
				DrawToScreen(ReturnedColour, x,y);
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

//float Ray::SoftShadows(Shape* _ShapeArray[], Intersect i)
//{
//	glm::vec3 ContactPoint = Origin + i.Distance*Direction;
//	glm::vec3 VecToLight = glm::normalize(arealight->position - ContactPoint);
//	//Intesection
//	Intersect intersect = CheckHit(_ShapeArray, ContactPoint + i.Normal*0.001f, VecToLight);
//	if (intersect.ObjectID == -1 || intersect.ObjectID == i.ObjectID)
//		return 1;
//	else
//		return 0;
//}

float Ray::SoftShadows(Shape * _ShapeArray[], Intersect i)
{
	float average = 0;
	glm::vec3 ContactPoint = Origin + i.Distance*Direction;
	glm::vec3 VecToLight;
	for (int z = 0; z < 64; z++) {
	VecToLight = glm::normalize(RandomPointInAreaLight() - ContactPoint);
	Intersect intersect = CheckHit(_ShapeArray, ContactPoint + i.Normal*0.001f, VecToLight);
	if (intersect.ObjectID == -1 || intersect.ObjectID == i.ObjectID)
		average ++;
	}
	return 1- (average/64);
}

glm::vec3 Ray::RandomPointInAreaLight()
{
	int rad = (arealight->radius)*10;
	float x = arealight->position.x + ((rand()%rad)/10) * cos(rand());
	float z = arealight->position.z + ((rand() % rad) / 10) * sin(rand());
	return glm::vec3(x, arealight->position.y, z);
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




