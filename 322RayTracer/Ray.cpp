#include "Ray.h"
#include <math.h>
Ray::Ray(float _Fov, int ScreenWidth, int ScreenHeight) {
	Origin = glm::vec3(0,0,0);
	width = ScreenWidth;
	height = ScreenHeight;
	ImageAspectRatio = float(width) / float(height);
	Fov = tan((_Fov * 3.14 / 180) / 2);
}

float Ray::PixelNormalized(int val,int secondVal)
{
	return ((float)val + 0.5)/secondVal;
}

int Ray::CheckHit(Shape* s[])
{
	int LowestID=-1;
	float LowestValue=99;
	float temp;
	for (int i = 0; i < AmountOfShapes; i++) {
		temp=s[i]->Intersection(Origin, Direction);
		if (temp != -1 && temp < LowestValue) {
			LowestValue = temp;
			LowestID = i;
		}
	}
	return LowestID;
}


void Ray::RayCast(glm::vec3** img, Shape* ShapeArray[],int Amount)
{
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
			int ShapeID = CheckHit(ShapeArray);
			if (ShapeID != -1) {
				img[x][y] = ShapeArray[ShapeID]->Colour;
			}
		}

	}//std::cout << WorldSpaceX << std::endl;
}




