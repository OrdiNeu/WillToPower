#include "PerlinNoiseGenerator.hpp"

// Formula and naming convention obtained from http://webstaff.itn.liu.se/~stegu/TNM022-2005/perlinnoiselinks/perlin-noise-math-faq.html

// Constants
PerlinNoiseGenerator* PerlinNoiseGenerator::instance = NULL;
const int PERLIN_WIDTH = 256;
const int PERLIN_HEIGHT = 256;

// Constructor
PerlinNoiseGenerator::PerlinNoiseGenerator() {
	// Generate the noise grid
	noiseGridX = new double*[PERLIN_WIDTH];
	noiseGridY = new double*[PERLIN_WIDTH];
	for (int i = 0; i < PERLIN_WIDTH; i++) {
		noiseGridX[i] = new double[PERLIN_HEIGHT];
		noiseGridY[i] = new double[PERLIN_HEIGHT];
		for (int j = 0; j < PERLIN_HEIGHT; j++) {
			// For each point, generate a random 2D unit vector
			float angle = 2*PI*((float) rand() / (float) RAND_MAX);
			noiseGridX[i][j] = sin(angle);
			noiseGridY[i][j] = cos(angle);
		}
	}
}

PerlinNoiseGenerator* PerlinNoiseGenerator::getInstance() {
	if (!instance) {
		instance = new PerlinNoiseGenerator;
	}
	return instance;
};

double PerlinNoiseGenerator::getNonPeriodic(double x, double y) {
	// Confine x and y to be within the boundaries
	x -= (int) (x/PERLIN_WIDTH) * PERLIN_WIDTH;
	y -= (int) (y/PERLIN_HEIGHT) * PERLIN_HEIGHT;
	if (x < 0) x = -x;
	if (y < 0) y = -y;
	
	// Obtain the perlin height from the corresponding nearest four neighbours
	int lowerx = (int) x;
	int lowery = (int) y;
	int upperx = lowerx + 1;
	int uppery = lowery + 1;
	
	double s = noiseGridX[lowerx][lowery] * (x - lowerx) + noiseGridY[lowerx][lowery] * (y - lowery);
	double t = noiseGridX[upperx][lowery] * (x - upperx) + noiseGridY[upperx][lowery] * (y - lowery);
	double u = noiseGridX[lowerx][uppery] * (x - lowerx) + noiseGridY[lowerx][uppery] * (y - uppery);
	double v = noiseGridX[upperx][uppery] * (x - upperx) + noiseGridY[upperx][uppery] * (y - uppery);
	
	double Sx = 3*pow(x-lowerx,2) - 2*pow(x-lowerx,3);
	double a = s + Sx*(t-s);
	double b = u + Sx*(v-u);
	double Sy = 3*pow(y-lowery,2) - 2*pow(y-lowery,3);
	return a + Sy*(b-a);
}

double PerlinNoiseGenerator::get(double x, double y) {
	// Confine x and y to be within the boundaries
	x -= (int) (x/PERLIN_WIDTH) * PERLIN_WIDTH;
	y -= (int) (y/PERLIN_HEIGHT) * PERLIN_HEIGHT;
	
	return (getNonPeriodic(x,y) * (PERLIN_WIDTH-x) * (PERLIN_HEIGHT-y) + \
			getNonPeriodic(x-PERLIN_WIDTH,y) * (x) * (PERLIN_HEIGHT-y) + \
			getNonPeriodic(x-PERLIN_WIDTH,y-PERLIN_HEIGHT) * (x) * (y) + \
			getNonPeriodic(x,y-PERLIN_HEIGHT) * (PERLIN_WIDTH-x) * (y)) / (PERLIN_WIDTH * PERLIN_HEIGHT);
}