#include "Ray.h"
#include <math.h>
Ray::Ray() {
	Origin = glm::vec3(0,0,0);
}

float Ray::PixelNormalized(int val,int secondVal)
{
	return ((float)val + 0.5)/secondVal;
}

void Ray::RayCast(glm::vec3** img)
{
	float ImageAspectRatio = width / height;
	float WorldSpaceX;//Normalised x of pixel
	float WorldSpaceY;//Normalised y of pixel
	float PixelCamerax;
	float PixelCameray;
	glm::vec3 Pcameraspace; 
	float fov = tan((30*3.14/180) / 2);
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			WorldSpaceX = ((2*PixelNormalized(x,width) - 1)*ImageAspectRatio);
			WorldSpaceY = (1 -2*PixelNormalized(y,height));
			PixelCamerax = WorldSpaceX * fov;
			PixelCameray = WorldSpaceY * fov;
			Pcameraspace = glm::vec3(PixelCamerax,PixelCameray,-1);
			Direction = Pcameraspace - Origin;
			Direction = glm::normalize(Direction);
			img[x][y] = Direction;
		}

	}//std::cout << WorldSpaceX << std::endl;
}


