#ifndef PERLIN_HPP
#define PERLIN_HPP
#include <iostream>
#include <cmath>
#include <cstdlib>

class PerlinNoiseGenerator {
public:
	static PerlinNoiseGenerator* getInstance();
	
	double get(double x, double y);
	double getNonPeriodic(double x, double y);
	double** noiseGridX;
	double** noiseGridY;
	//TODO: Add a random seed
private:
	static PerlinNoiseGenerator* instance;
	
	// Block construction and destruction of the instance except by getInstance();
	PerlinNoiseGenerator();
	~PerlinNoiseGenerator();
};

#endif