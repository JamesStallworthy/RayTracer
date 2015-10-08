#include <iostream>
#include <fstream>
#include <C:\Users\james\Documents\GitHub\332RayTracer\glm-0.9.6.3\glm\glm.hpp>
//using namespace std;
int width = 640;
int height = 480;
glm::vec3 image[640][480];

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
	Fill_Image();
	Save_Image();

	std::cin.get();
	return 0;
}