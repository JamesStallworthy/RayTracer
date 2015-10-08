#include "Ray.h"
#include <math.h>
Ray::Ray() {
	Origin = glm::vec3(0,0,0);
	ImageAspectRatio = width / height;
}

float Ray::PixelNormalized(int val,int secondVal)
{
	return ((float)val + 0.5)/secondVal;
}

void Ray::RayCast(glm::vec3** img)
{
	 
	float RemappedX;//Normalised x of pixel
	float RemappedY;//Normalised y of pixel
	float WorldSpacex;
	float WorldSpacey;
	glm::vec3 Pcameraspace; 
	float fov = tan((30*3.14/180) / 2);
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			RemappedX = ((2*PixelNormalized(x,width) - 1)*ImageAspectRatio);
			RemappedY = (1 -2*PixelNormalized(y,height));
			WorldSpacex = RemappedX * fov;
			WorldSpacey = RemappedY * fov;
			Pcameraspace = glm::vec3(WorldSpacex, WorldSpacey,-1);
			Direction = glm::normalize(Pcameraspace - Origin);

			img[x][y] = Direction;
		}

	}//std::cout << WorldSpaceX << std::endl;
}


