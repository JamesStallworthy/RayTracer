//#include <SDL.h>
#include <iostream>

#include <fstream>
#include <glm.hpp>
#include "Shape.h"
#include "Ray.h"
#include "Sphere.h"
#include <time.h>

//using namespace std;
int width = 640;
int height = 480;
glm::vec3 **image = new glm::vec3*[width];

Ray ray(30, width, height);
//Sphere One(glm::vec3(0, 0, -20), 4, glm::vec3(0, 0, 1));
Shape* One = new Sphere(glm::vec3(0, 0, -20), 4, glm::vec3(1, 0.32, 0.36));
Shape* Two = new Sphere(glm::vec3(5, -1, -15), 2, glm::vec3(0.9, 0.76, 0.46));
Shape* Three = new Sphere(glm::vec3(5, 0, -25), 3, glm::vec3(0.65, 0.77, 0.97));
Shape* Four = new Sphere(glm::vec3(-5.5, 0, -15), 3, glm::vec3(0.90, 0.9, 0.9));
Shape* ShapeArray[4];

void Fill_Image() {
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			image[x][y] = glm::vec3(1, 1, 0);
		}
	}
}

void Save_Image() {
	std::ofstream ofs("./untitled.pmm", std::ios::out | std::ios::binary);
	ofs << "P6\n" << width << " " << height << "\n255\n";
	for (unsigned y = 0; y < height; ++y) {
		for (unsigned x = 0; x < width; ++x) {
			ofs << (unsigned char)(std::fmin((float)1, (float)image[x][y].x) * 255) <<
				(unsigned char)(std::fmin((float)1, (float)image[x][y].y) * 255) <<
				(unsigned char)(std::fmin((float)1, (float)image[x][y].z) * 255);
		}
	}
	ofs.close();
}


int main() {
	ShapeArray[0] = One;
	ShapeArray[1] = Two;
	ShapeArray[2] = Three;
	ShapeArray[3] = Four;
	//fill image array
	for (int i(0); i < width; i++) image[i] = new glm::vec3[height];
	//Fill_Image();
	clock_t t;
	t = clock();
	ray.RayCast(image,ShapeArray,4);
	t = clock() - t;
	std::cout << "Time: " << (float)t / CLOCKS_PER_SEC << std::endl;
	Save_Image();
	std::cin.get();
	return 0;

}