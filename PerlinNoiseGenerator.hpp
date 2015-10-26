#ifndef PERLIN_HPP
#define PERLIN_HPP

#include <iostream>
#include <cmath>
#include <cstdlib>

class PerlinNoiseGenerator {
public:
	double get(double x, double y);
	double getNonPeriodic(double x, double y);
	void smooth();
	void smooth(double intensity);
	double** noiseGridX;
	double** noiseGridY;
	int seed;
	PerlinNoiseGenerator(int seed);
};

#endif