#ifndef PERLIN_HPP
#define PERLIN_HPP
#include <iostream>
#include <cmath>
#include <cstdlib>

class PerlinNoiseGenerator {
public:
	static PerlinNoiseGenerator* getInstance();
	PerlinNoiseGenerator();
	
	double get(double x, double y);
	double getNonPeriodic(double x, double y);
	double** noiseGridX;
	double** noiseGridY;
private:
	static PerlinNoiseGenerator* instance;
};

const double PI = 3.141592653589793238463;

#endif