#ifndef RGBAPIXEL_H
#define RGBAPIXEL_H

class RGBAPixel {
public:
	unsigned char r;
	unsigned char g;
	unsigned char b;
	double a;
	RGBAPixel();
	RGBAPixel(int red, int green, int blue);
	RGBAPixel(int red, int green, int blue, double alpha);
};

#endif