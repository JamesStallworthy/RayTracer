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

float DirectionCam = -1;//For camera movement
float DirectionSphere = -1;//For ball movement
bool CamMove = false;//Camera moving
bool SphereMove = false;// Sphere moving

glm::vec3 **image = new glm::vec3*[width]; //Image array for storing pixel colours, used for saving to file
Light light(glm::vec3(0,15,0),1);//point light
AreaLight arealight(glm::vec3(0, 15, 0), 5, 1, 4);

Ray ray(80, width, height, &light, &arealight, 21);//Main ray tracing class

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
Shape* Mirror1 = new Sphere(glm::vec3(15, 4, -24), 5, glm::vec3(1, 1, 0), 0.1, 10, true, 1, 0.07);
Shape* Mirror2 = new Sphere(glm::vec3(-25, 6, -35), 5, glm::vec3(0.6, 0.6, 0.6), 0.1, 10, true, 1, 0.1);

//Floor
Shape* plane = new Plane(glm::vec3(0, -4, -20), glm::vec3(0, 1, 0), glm::vec3(0.2, 0.2, 0.2),0.1,10000, false, 1, 1);

//Triangle Pyramid
Shape* triangle = new Triangle(glm::vec3(-10, -3, -20), glm::vec3(-20, -3, -20), glm::vec3(-15, 4, -25), glm::vec3(1, 0, 0),0.1,2, false, 1, 0.1);
Shape* triangle2 = new Triangle(glm::vec3(-20, -3, -30), glm::vec3(-10, -3, -30), glm::vec3(-15, 4, -25), glm::vec3(1, 0, 0), 0.1, 2, false, 1, 0.1);
Shape* triangle3 = new Triangle(glm::vec3(-20, -3, -20), glm::vec3(-20, -3, -30), glm::vec3(-15, 4, -25), glm::vec3(1, 0, 0), 0.1, 2, false, 1, 0.1);
Shape* triangle4 = new Triangle(glm::vec3(-10, -3, -30), glm::vec3(-10, -3, -20), glm::vec3(-15, 4, -25), glm::vec3(1, 0, 0), 0.1, 2, false, 1, 0.1);

//Shape* poly2 = new Poly(glm::vec3(4, -3, -10), glm::vec3(4, -3, -11), glm::vec3(4, -4, -10), glm::vec3(4, -4, -11), glm::vec3(1, 1, 1), 0.1, 100, false, 1, 0.1);

Shape* ShapeArray[21];// Array storing all shapes

//Save image to file
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

//Create the 2D array
void fillImageArray() {
	for (int i = 0; i < width; i++) image[i] = new glm::vec3[height];
}

//Makes all pixels in image array black
void clearImageArray() {
	//fill image array
	for (int x = 0; x < width; x++)
		for (int y = 0; y < height; y++)
			image[x][y] = glm::vec3(0, 0, 0);
}

//Call raycast function and time
void render() {
	t = clock();
	clearImageArray();
	ray.RayCast(image, ShapeArray);
	t = clock() - t;
	std::cout << "Frame took: " << (float)t / CLOCKS_PER_SEC << " seconds to render."<< std::endl;
}

bool Controls(SDL_Window* _window) {
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
			else if (event.key.keysym.sym == SDLK_LSHIFT) {
				ray.Origin.y++;
				render();
			}
			else if (event.key.keysym.sym == SDLK_LCTRL) {
				ray.Origin.y--;
				render();
			}
			else if (event.key.keysym.sym == SDLK_z) {
				CamMove = !CamMove;
			}
			else if (event.key.keysym.sym == SDLK_x) {
				SphereMove = !SphereMove;
			}
			else if (event.key.keysym.sym == SDLK_f) {
				ray.Shadows = !ray.Shadows;
				render();
			}
		}
	}
	return true;

}

//Animate the light movement	
void movelight() {
	if (light.Position.z < -50)
		DirectionCam = 1;
	if (light.Position.z > 0)
		DirectionCam = -1;
	light.Position.z = light.Position.z + DirectionCam;
}
//Animate the sphere movement
void movesphere() {
	if (Mirror2->GetOrigin().x < -30)
		DirectionSphere = 1;
	if (Mirror2->GetOrigin().x > 30)
		DirectionSphere = -1;
	Mirror2->SetOrigin(Mirror2->GetOrigin() + glm::vec3(DirectionSphere,0,0));
}

int main(int argc, char *argv[]) {

	//SDL init
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window *window;
	window = SDL_CreateWindow("Raytracer - James Stallworthy", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, NULL);
	SDL_Surface *surface = SDL_GetWindowSurface(window);

	//Pass window parameters to raytacer
	ray.SetWindow(window, surface);

	//Get soft shadow sample from user
	int samples;
	std::cout << "How many softshadow samples: " << std::endl;
	std::cin >> samples;
	std::cout << "Rendering...." << std::endl;
	arealight.samples = samples;

	//Assign shapes to the shape array
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

	bool Display = true;//Keep window open

	fillImageArray(); //Create 2D array

	SDL_Event event;
	
	render();//Render initial frame

	//Display controls 
	std::cout << "\n---------------------------------\n";
	std::cout << "WASD keys to move camera \nShift and Ctrl to move up and down\nZ to activate moving light\nX to activate moving mirror sphere\nF to toggle shadows" << std::endl;
	std::cout << "\n---------------------------------\n";


	while (Display) {
		//if display == false close program
		if (CamMove)//If camera move, call light animation function
			movelight();
		if (SphereMove)//If sphere move, call sphere animation function
			movesphere();
		if (CamMove||SphereMove)//if ball is moving or cam is moving update screen every frame
			render();
		Display = Controls(window);
	}
	Save_Image(); // Save image before closing program
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}