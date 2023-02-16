#include <stdio.h>
#include "RGBAPixel.h"

RGBAPixel::RGBAPixel() {
	r = 255;
	g = 255;
	b = 255;
	a = 1;
}

RGBAPixel::RGBAPixel(int red, int green, int blue) {
	r = red;
	g = green;
	b = blue;
	a = 0;
}

RGBAPixel::RGBAPixel(int red, int green, int blue, double alpha) {
	r = red;
	g = green;
	b = blue;
	a = alpha;
}

