#include "PerlinNoiseGenerator.hpp"

const int PERLIN_WIDTH = 512;
const int PERLIN_HEIGHT = 512;

PerlinNoiseGenerator::PerlinNoiseGenerator(int seed) : seed(seed) {
	srand(seed);

	// Generate the noise grid
	noiseGridX = new double*[PERLIN_WIDTH];
	noiseGridY = new double*[PERLIN_WIDTH];
	for (int i = 0; i < PERLIN_WIDTH; i++) {
		noiseGridX[i] = new double[PERLIN_HEIGHT];
		noiseGridY[i] = new double[PERLIN_HEIGHT];
		for (int j = 0; j < PERLIN_HEIGHT; j++) {
			// For each point, generate a random 2D unit vector. We also divide it by 2 to save time later
			float angle = 2*3.14159*((float) rand() / (float) RAND_MAX);
			noiseGridX[i][j] = sin(angle)/2;
			noiseGridY[i][j] = cos(angle)/2;
		}
	}
}

// Smooths the noise grid
void PerlinNoiseGenerator::smooth(double intensity) {
	double** newNoiseX;
	double** newNoiseY;
	newNoiseX = new double*[PERLIN_WIDTH];
	newNoiseY = new double*[PERLIN_WIDTH];
	for (int x = 0; x < PERLIN_WIDTH; x++) {
		newNoiseX[x] = new double[PERLIN_HEIGHT];
		newNoiseY[x] = new double[PERLIN_HEIGHT];
		for (int y = 0; y < PERLIN_HEIGHT; y++) {
			// Average the surrounding eight points
			int surround_x[] = {x-1, x-1, x-1, x, x, x+1, x+1, x+1};
			int surround_y[] = {y-1, y, y+1, y-1, y+1, y-1, y, y+1};
			double averageX = 0.0;
			double averageY = 0.0;
			for (int i = 0; i < 8; i++) {
				averageX += newNoiseX[surround_x[i]][surround_y[i]];
				averageY += newNoiseY[surround_x[i]][surround_y[i]];
			}
			averageX /= 8;
			averageY /= 8;
			noiseGridX[x][y] += (averageX-noiseGridX[x][y])*(intensity+1)/intensity;
			noiseGridY[x][y] += (averageX-noiseGridY[x][y])*(intensity+1)/intensity;
		}
	}
}

void PerlinNoiseGenerator::smooth() {
	this->smooth(1.0);
}

double PerlinNoiseGenerator::getNonPeriodic(double x, double y) {
	// Confine x and y to be within the boundaries
	x -= (int) (x/PERLIN_WIDTH) * PERLIN_WIDTH;
	y -= (int) (y/PERLIN_HEIGHT) * PERLIN_HEIGHT;
	if (x < 0) x = -x;
	if (y < 0) y = -y;
	
	// Obtain the perlin height from the corresponding nearest four neighbours
	// Naming convention / formula obtained from http://webstaff.itn.liu.se/~stegu/TNM022-2005/perlinnoiselinks/perlin-noise-math-faq.html
	int lowerx = (int) x;
	int lowery = (int) y;
	int upperx = (lowerx + 1) % PERLIN_WIDTH;
	int uppery = (lowery + 1) % PERLIN_HEIGHT;
	
	// Get the contribution from the four surrounding grid points. Note that we have previously halved noiseGrid
	double s = noiseGridX[lowerx][lowery] * (1 - (x - lowerx)) + noiseGridY[lowerx][lowery] * (1 - (y - lowery));
	double t = noiseGridX[upperx][lowery] * (1 - (x - upperx)) + noiseGridY[upperx][lowery] * (1 - (y - lowery));
	double u = noiseGridX[lowerx][uppery] * (1 - (x - lowerx)) + noiseGridY[lowerx][uppery] * (1 - (y - uppery));
	double v = noiseGridX[upperx][uppery] * (1 - (x - upperx)) + noiseGridY[upperx][uppery] * (1 - (y - uppery));

	double Sx = 3*pow(x-lowerx,2) - 2*pow(x-lowerx,3);
	double a = s + Sx*(t-s);
	double b = u + Sx*(v-u);
	double Sy = 3*pow(y-lowery,2) - 2*pow(y-lowery,3);
	return a + Sy*(b-a);
}

double PerlinNoiseGenerator::get(double x, double y) {
	// Confine x and y to be within the boundaries
	x -= int(x/PERLIN_WIDTH) * PERLIN_WIDTH;
	y -= int(y/PERLIN_HEIGHT) * PERLIN_HEIGHT;
	
	//std::cout << "Returning: " << getNonPeriodic(x,y) << "," << getNonPeriodic(x-PERLIN_WIDTH,y) << "," << getNonPeriodic(x-PERLIN_WIDTH,y-PERLIN_HEIGHT) << "," << getNonPeriodic(x,y-PERLIN_HEIGHT) << std::endl;
	return (getNonPeriodic(x,y) * (PERLIN_WIDTH-x) * (PERLIN_HEIGHT-y) + \
			getNonPeriodic(x-PERLIN_WIDTH,y) * (x) * (PERLIN_HEIGHT-y) + \
			getNonPeriodic(x-PERLIN_WIDTH,y-PERLIN_HEIGHT) * (x) * (y) + \
			getNonPeriodic(x,y-PERLIN_HEIGHT) * (PERLIN_WIDTH-x) * (y)) / (PERLIN_WIDTH * PERLIN_HEIGHT);
}