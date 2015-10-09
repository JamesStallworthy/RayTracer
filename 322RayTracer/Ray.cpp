#include "Ray.h"
#include <math.h>
Ray::Ray() {
	Origin = glm::vec3(0,0,0);
	ImageAspectRatio = float(width) / float(height);
	
}

float Ray::PixelNormalized(int val,int secondVal)
{
	return ((float)val + 0.5)/secondVal;
}

int Ray::CheckHit(Shape* s[])
{
	if (s[0]->Intersection(Origin, Direction) != -1) {
		return 0;
	}
	return -1;
}


void Ray::RayCast(glm::vec3** img, Shape* ShapeArray[],int Amount)
{
	AmountOfShapes = Amount;
	
	float RemappedX;//Normalised x of pixel
	float RemappedY;//Normalised y of pixel
	float WorldSpacex;
	float WorldSpacey;
	glm::vec3 Pcameraspace; 
	float fov = tan((90*3.14/180) / 2);
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			RemappedX = ((2*PixelNormalized(x,width) - 1)*ImageAspectRatio);
			RemappedY = (1 -2*PixelNormalized(y,height));
			WorldSpacex = RemappedX * fov;
			WorldSpacey = RemappedY * fov;
			Pcameraspace = glm::vec3(WorldSpacex, WorldSpacey,-1);
			Direction = glm::normalize(Pcameraspace - Origin);
			int ShapeID;
			ShapeID = CheckHit(ShapeArray);
			if (ShapeID != -1) {
				img[x][y] == ShapeArray[ShapeID]->Colour;
			}
		}

	}//std::cout << WorldSpaceX << std::endl;
}




