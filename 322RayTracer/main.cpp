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
AreaLight arealight(glm::vec3(0, 10, 0), 5, 1, 17);
Ray ray(80, width, height, &light, &arealight, 21);

//Sphere Pyramid
Shape* One = new Sphere(glm::vec3(0, -2, -20), 2, glm::vec3(0, 0.2, 0.7),0.1,100, false, 1, 0.5);
Shape* Two = new Sphere(glm::vec3(0, -2, -24), 2, glm::vec3(0, 0.2, 0.7), 0.1, 100, false, 1, 0.5);
Shape* Three = new Sphere(glm::vec3(0, -2, -28), 2, glm::vec3(0, 0.2, 0.7), 0.1, 100, false, 1, 0.5);
Shape* Four = new Sphere(glm::vec3(-4, -2, -24), 2, glm::vec3(0, 0.2, 0.7), 0.1, 100, false, 1, 0.5);
Shape* Five = new Sphere(glm::vec3(4, -2, -20), 2, glm::vec3(0, 0.2, 0.7), 0.1, 100, false, 1, 0.5);
Shape* Six = new Sphere(glm::vec3(4, -2, -24), 2, glm::vec3(0, 0.2, 0.7), 0.1, 100, false, 1, 0.5);
Shape* Seven = new Sphere(glm::vec3(4, -2, -28), 2, glm::vec3(0, 0.2, 0.7), 0.1, 100, false, 1, 0.5);
Shape* Eight = new Sphere(glm::vec3(-4, -2, -20), 2, glm::vec3(0, 0.2, 0.7), 0.1, 100, false, 1, 0.5);
Shape* Nine = new Sphere(glm::vec3(-4, -2, -28), 2, glm::vec3(0, 0.2, 0.7), 0.1, 100, false, 1, 0.5);
Shape* Ten = new Sphere(glm::vec3(-2, 1, -22), 2, glm::vec3(0, 0.2, 0.7), 0.1, 100, false, 1, 0.5);
Shape* Eleven = new Sphere(glm::vec3(-2, 1, -26), 2, glm::vec3(0, 0.2, 0.7), 0.1, 100, false, 1, 0.5);
Shape* Twelve = new Sphere(glm::vec3(2, 1, -22), 2, glm::vec3(0, 0.2, 0.7), 0.1, 100, false, 1, 0.5);
Shape* Thirteen = new Sphere(glm::vec3(2, 1, -26), 2, glm::vec3(0, 0.2, 0.7), 0.1, 100, false, 1, 0.5);
Shape* Fourteen = new Sphere(glm::vec3(0, 4, -24), 2, glm::vec3(0, 0.2, 0.7), 0.1, 100, true, 1, 0.2);

//Mirrow Balls
Shape* Mirror1 = new Sphere(glm::vec3(15, 4, -24), 5, glm::vec3(1, 1, 0), 0.1, 100, true, 1, 0.1);
Shape* Mirror2 = new Sphere(glm::vec3(-25, 4, -30), 5, glm::vec3(0.6, 0.6, 0.6), 0.1, 100, true, 1, 0.1);

Shape* plane = new Plane(glm::vec3(0, -4, -20), glm::vec3(0, 1, 0), glm::vec3(0.2, 0.2, 0.2),0.1,100, false, 1, 1);

//Triangle Pyramid
Shape* triangle = new Triangle(glm::vec3(-20, -3, -20), glm::vec3(-10, -3, -20), glm::vec3(-15, 4, -25), glm::vec3(1, 0, 0),0.1,100, false, 1, 0.1);
Shape* triangle2 = new Triangle(glm::vec3(-20, -3, -30), glm::vec3(-10, -3, -30), glm::vec3(-15, 4, -25), glm::vec3(1, 0, 0), 0.1, 100, false, 1, 0.1);
Shape* triangle3 = new Triangle(glm::vec3(-20, -3, -30), glm::vec3(-20, -3, -20), glm::vec3(-15, 4, -25), glm::vec3(1, 0, 0), 0.1, 100, false, 1, 0.1);
Shape* triangle4 = new Triangle(glm::vec3(-10, -3, -20), glm::vec3(-10, -3, -30), glm::vec3(-15, 4, -25), glm::vec3(1, 0, 0), 0.1, 100, false, 1, 0.1);

//Shape* poly2 = new Poly(glm::vec3(4, -3, -10), glm::vec3(4, -3, -11), glm::vec3(4, -4, -10), glm::vec3(4, -4, -11), glm::vec3(1, 1, 1), 0.1, 100, false, 1, 0.1);
Shape* ShapeArray[21];


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
	ShapeArray[4] = Five;
	ShapeArray[5] = plane;
	ShapeArray[6] = Six;
	ShapeArray[7] = Seven;
	ShapeArray[8] = Eight;
	ShapeArray[9] = Nine;
	ShapeArray[10] = Ten;
	ShapeArray[11] = Eleven;
	ShapeArray[12] = Twelve;
	ShapeArray[13] = Thirteen;
	ShapeArray[14] = Fourteen;
	ShapeArray[15] = Mirror1;
	ShapeArray[16] = triangle;
	ShapeArray[17] = triangle2;
	ShapeArray[18] = triangle3;
	ShapeArray[19] = triangle4;
	ShapeArray[20] = Mirror2;
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