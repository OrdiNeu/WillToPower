#ifndef BOUNDS_CHECK_HPP
#define BOUNDS_CHECK_HPP

// Swaps the bounds if x0 > x1
inline void checkBounds(float* x0, float* x1) {
	float temp = *x0;
	*x0 = (temp < *x1) ? *x0 : *x1;
	*x1 = (temp < *x1) ? *x1 : temp;
}

inline void checkBounds(float* x0, float* x1, float* y0, float* y1) {
	checkBounds(x0, x1);
	checkBounds(y0, y1);
}

inline void checkBounds(int* x0, int* x1) {
	int temp = *x0;
	*x0 = (temp < *x1) ? *x0 : *x1;
	*x1 = (temp < *x1) ? *x1 : temp;
}

inline void checkBounds(int* x0, int* x1, int* y0, int* y1) {
	checkBounds(x0, x1);
	checkBounds(y0, y1);
}

#endif