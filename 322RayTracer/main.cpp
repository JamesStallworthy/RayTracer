#include <iostream>
#include <fstream>
#include <glm.hpp>
#include "Shape.h"
#include "Ray.h"
#include "Sphere.h"
#include "Plane.h"
#include "Poly.h"
#include <time.h>
#include "Triangle.h"
#include "Light.h"
#include <SDL.h>
#include "AreaLight.h"
SDL_Event event;
clock_t t;

int width = 640;
int height = 480;

glm::vec3 **image = new glm::vec3*[width];
Light light(glm::vec3(0,10,0),1);
AreaLight arealight(glm::vec3(0, 10, 0), 5, 1, 16);
Ray ray(80, width, height, NULL, &arealight, 8);
Shape* One = new Sphere(glm::vec3(0, 0, -20), 4, glm::vec3(1, 0.32, 0.36),0.1,100, true);
Shape* Two = new Sphere(glm::vec3(5, -1, -15), 2, glm::vec3(0.9, 0.76, 0.46),0.1,100, true);
Shape* Three = new Sphere(glm::vec3(5, 0, -25), 3, glm::vec3(0.65, 0.77, 0.97),0.1,100, false);
Shape* Four = new Sphere(glm::vec3(-5.5, 0, -15), 3, glm::vec3(0.90, 0.9, 0.9),0.1,100, false);
Shape* plane = new Plane(glm::vec3(0, -4, -20), glm::vec3(0, 1, 0), glm::vec3(0.2, 0.2, 0.2),0.1,100, false);
Shape* poly = new Poly(glm::vec3(4, -3, -10), glm::vec3(5, -3, -10), glm::vec3(4, -4, -10), glm::vec3(5, -4, -10), glm::vec3(1, 1, 1), 0.1, 100, false);
Shape* poly2 = new Poly(glm::vec3(4, -3, -10), glm::vec3(4, -3, -11), glm::vec3(4, -4, -10), glm::vec3(4, -4, -11), glm::vec3(1, 1, 1), 0.1, 100, false);
Shape* triangle = new Triangle(glm::vec3(0, -1, -5), glm::vec3(2, -1, -5), glm::vec3(1, -1, -15), glm::vec3(1, 0, 0),0.1,100, false);
Shape* ShapeArray[8];

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

void fillImageArray() {
	//fill image array
	for (int i = 0; i < width; i++) image[i] = new glm::vec3[height];
}

void clearImageArray() {
	//fill image array
	for (int x = 0; x < width; x++)
		for (int y = 0; y < height; y++)
			image[x][y] = glm::vec3(0, 0, 0);
}

void render() {
	t = clock();
	clearImageArray();
	ray.RayCast(image, ShapeArray);
	t = clock() - t;
	std::cout << "Time: " << (float)t / CLOCKS_PER_SEC << std::endl;
}

bool Controls() {

	if (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			return false;
		}
		if (event.type == SDL_KEYDOWN) {
			if(event.key.keysym.sym == SDLK_a) {
				ray.Origin.x--;
				render();
			}
			else if (event.key.keysym.sym == SDLK_d) {
				ray.Origin.x++;
				render();
			}
			else if (event.key.keysym.sym == SDLK_w) {
				ray.Origin.z--;
				render();
			}
			else if (event.key.keysym.sym == SDLK_s) {
				ray.Origin.z++;
				render();
			}
		}
	}

}

int main(int argc, char *argv[]) {
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window *window;
	window = SDL_CreateWindow("Raycaster", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, NULL);
	SDL_Surface *surface = SDL_GetWindowSurface(window);
	ray.SetWindow(window, surface);
	
	ShapeArray[0] = One;
	ShapeArray[1] = Two;
	ShapeArray[2] = Three;
	ShapeArray[3] = Four;
	ShapeArray[4] = plane;
	ShapeArray[5] = triangle;
	ShapeArray[6] = poly;
	ShapeArray[7] = poly2;
	

	bool Display = true;
	fillImageArray();
	SDL_Event event;
	render();
	while (Display) {
		//if Controls returns false close program
		Display = Controls();
	}
	Save_Image();
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}