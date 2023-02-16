#include "stats.h"


#include "stats.h"
#include <cstdlib>
stats::stats(PNG & im){
    unsigned int height = im.height();
    unsigned int width = im.width();
    sumRed.resize(height);
    sumGreen.resize(height);
    sumBlue.resize(height);
    sumsqRed.resize(height);
    sumsqGreen.resize(height);
    sumsqBlue.resize(height);
    for (unsigned int y=0; y<height; y++) {
        sumRed[y].resize(width);
        sumGreen[y].resize(width);
        sumBlue[y].resize(width);
        sumsqRed[y].resize(width);
        sumsqGreen[y].resize(width);
        sumsqBlue[y].resize(width);
        for (unsigned int x=0; x<width; x++) {
            RGBAPixel *new_pixel = im.getPixel(x,y);
            if (x==0 && y==0) {
                sumRed[y][x] = new_pixel->r;
                sumGreen[y][x] = new_pixel->g;
                sumBlue[y][x] = new_pixel->b;
                sumsqRed[y][x] = new_pixel->r*new_pixel->r ;
                sumsqGreen[y][x] = new_pixel->g*new_pixel->g;
                sumsqBlue[y][x] = new_pixel->b*new_pixel->b;
            }
            else if (x==0 && y!=0) {
                sumRed[y][x] = sumRed[y-1][0] + new_pixel->r;
                sumGreen[y][x] = sumGreen[y-1][0] + new_pixel->g;
                sumBlue[y][x] = sumBlue[y-1][0] + new_pixel->b;
                sumsqRed[y][x] = sumsqRed[y-1][0] + new_pixel->r*new_pixel->r ;
                sumsqGreen[y][x] = sumsqGreen[y-1][0] + new_pixel->g*new_pixel->g;
                sumsqBlue[y][x] = sumsqBlue[y-1][0] + new_pixel->b*new_pixel->b;
            }
            else if (x!=0 && y==0) {
                sumRed[y][x] = sumRed[0][x-1] + new_pixel->r;
                sumGreen[y][x] = sumGreen[0][x-1] + new_pixel->g;
                sumBlue[y][x] = sumBlue[0][x-1] + new_pixel->b;
                sumsqRed[y][x] = sumsqRed[0][x-1] + new_pixel->r*new_pixel->r ;
                sumsqGreen[y][x] = sumsqGreen[0][x-1] + new_pixel->g*new_pixel->g;
                sumsqBlue[y][x] = sumsqBlue[0][x-1] + new_pixel->b*new_pixel->b;
            }
            else {
                sumRed[y][x] = sumRed[y-1][x] + sumRed[y][x-1] - sumRed[y-1][x-1] + new_pixel->r;
                sumGreen[y][x] = sumGreen[y-1][x] + sumGreen[y][x-1] - sumGreen[y-1][x-1] + new_pixel->g;
                sumBlue[y][x] = sumBlue[y-1][x] + sumBlue[y][x-1] - sumBlue[y-1][x-1] + new_pixel->b;
                sumsqRed[y][x] = sumsqRed[y-1][x] + sumsqRed[y][x-1] - sumsqRed[y-1][x-1] + new_pixel->r*new_pixel->r ;
                sumsqGreen[y][x] = sumsqGreen[y-1][x] + sumsqGreen[y][x-1] - sumsqGreen[y-1][x-1] + new_pixel->g*new_pixel->g;
                sumsqBlue[y][x] = sumsqBlue[y-1][x] + sumsqBlue[y][x-1] - sumsqBlue[y-1][x-1] + new_pixel->b*new_pixel->b;
            }
        }
    }
}


long stats::getSum(char channel, pair<int,int> ul, int w, int h){
    long ret = 0;
    
    if (w<1 || h<1) { //might be wrong
        return 0;
    }
    if (channel == 'r') {
        if (ul.first == 0 && ul.second == 0) {
            return sumRed[ul.second+h-1][ul.first+w-1];
        }
        else if (ul.first == 0 && ul.second != 0) {
            long left = sumRed[ul.second-1][ul.first+w-1];
            long total = sumRed[ul.second+h-1][ul.first+w-1];
            ret = total - left;
        }
        else if (ul.first != 0 && ul.second == 0) {
            long right = sumRed[ul.second+h-1][ul.first-1];
            long total = sumRed[ul.second+h-1][ul.first+w-1];
            ret = total - right;
        }
        else {
            long right = sumRed[ul.second+h-1][ul.first-1];
            long left = sumRed[ul.second-1][ul.first+w-1];
            long mid = sumRed[ul.second-1][ul.first-1];
            long total = sumRed[ul.second+h-1][ul.first+w-1];
            ret = total + mid - left - right;
        }
    }
    else if (channel == 'g') {
        if (ul.first == 0 && ul.second == 0) {
            return sumGreen[ul.second+h-1][ul.first+w-1];
        }
        else if (ul.first == 0 && ul.second != 0) {
            long left = sumGreen[ul.second-1][ul.first+w-1];
            long total = sumGreen[ul.second+h-1][ul.first+w-1];
            ret = total - left;
        }
        else if (ul.first != 0 && ul.second == 0) {
            long right = sumGreen[ul.second+h-1][ul.first-1];
            long total = sumGreen[ul.second+h-1][ul.first+w-1];
            ret = total - right;
        }
        else {
            long right = sumGreen[ul.second+h-1][ul.first-1];
            long left = sumGreen[ul.second-1][ul.first+w-1];
            long mid = sumGreen[ul.second-1][ul.first-1];
            long total = sumGreen[ul.second+h-1][ul.first+w-1];
            ret = total + mid - left - right;
        }
    }
    else if (channel == 'b') {
        if (ul.first == 0 && ul.second == 0) {
            return sumBlue[ul.second+h-1][ul.first+w-1];
        }
        else if (ul.first == 0 && ul.second != 0) {
            long left = sumBlue[ul.second-1][ul.first+w-1];
            long total = sumBlue[ul.second+h-1][ul.first+w-1];
            ret = total - left;
        }
        else if (ul.first != 0 && ul.second == 0) {
            long right = sumBlue[ul.second+h-1][ul.first-1];
            long total = sumBlue[ul.second+h-1][ul.first+w-1];
            ret = total - right;
        }
        else {
            long right = sumBlue[ul.second+h-1][ul.first-1];
            long left = sumBlue[ul.second-1][ul.first+w-1];
            long mid = sumBlue[ul.second-1][ul.first-1];
            long total = sumBlue[ul.second+h-1][ul.first+w-1];
            ret = total + mid - left - right;
        }
    }
    else {
        cout << "Channel is not right" << endl;
    }

    return ret;
}

long stats::getSumSq(char channel, pair<int,int> ul, int w, int h){
    long ret = 0;
    if (w<1 || h<1) { //might be wrong
        return 0;
    }
    if (channel == 'r') {
        if (ul.first == 0 && ul.second == 0) {
            return sumsqRed[ul.second+h-1][ul.first+w-1];
        }
        else if (ul.first == 0 && ul.second != 0) {
            long left = sumsqRed[ul.second-1][ul.first+w-1];
            long total = sumsqRed[ul.second+h-1][ul.first+w-1];
            ret = total - left;
        }
        else if (ul.first != 0 && ul.second == 0) {
            long right = sumsqRed[ul.second+h-1][ul.first-1];
            long total = sumsqRed[ul.second+h-1][ul.first+w-1];
            ret = total - right;
        }
        else {
            long right = sumsqRed[ul.second+h-1][ul.first-1];
            long left = sumsqRed[ul.second-1][ul.first+w-1];
            long mid = sumsqRed[ul.second-1][ul.first-1];
            long total = sumsqRed[ul.second+h-1][ul.first+w-1];
            ret = total + mid - left - right;
        }
    }
    else if (channel == 'g') {
        if (ul.first == 0 && ul.second == 0) {
            return sumsqGreen[ul.second+h-1][ul.first+w-1];
        }
        else if (ul.first == 0 && ul.second != 0) {
            long left = sumsqGreen[ul.second-1][ul.first+w-1];
            long total = sumsqGreen[ul.second+h-1][ul.first+w-1];
            ret = total - left;
        }
        else if (ul.first != 0 && ul.second == 0) {
            long right = sumsqGreen[ul.second+h-1][ul.first-1];
            long total = sumsqGreen[ul.second+h-1][ul.first+w-1];
            ret = total - right;
        }
        else {
            long right = sumsqGreen[ul.second+h-1][ul.first-1];
            long left = sumsqGreen[ul.second-1][ul.first+w-1];
            long mid = sumsqGreen[ul.second-1][ul.first-1];
            long total = sumsqGreen[ul.second+h-1][ul.first+w-1];
            ret = total + mid - left - right;
        }
    }
    else if (channel == 'b') {
        if (ul.first == 0 && ul.second == 0) {
            return sumsqBlue[ul.second+h-1][ul.first+w-1];
        }
        else if (ul.first == 0 && ul.second != 0) {
            long left = sumsqBlue[ul.second-1][ul.first+w-1];
            long total = sumsqBlue[ul.second+h-1][ul.first+w-1];
            ret = total - left;
        }
        else if (ul.first != 0 && ul.second == 0) {
            long right = sumsqBlue[ul.second+h-1][ul.first-1];
            long total = sumsqBlue[ul.second+h-1][ul.first+w-1];
            ret = total - right;
        }
        else {
            long right = sumsqBlue[ul.second+h-1][ul.first-1];
            long left = sumsqBlue[ul.second-1][ul.first+w-1];
            long mid = sumsqBlue[ul.second-1][ul.first-1];
            long total = sumsqBlue[ul.second+h-1][ul.first+w-1];
            ret = total + mid - left - right;
        }
    }
    else {
        cout << "Channel is not right" << endl;
    }

    return ret;
}

// given a rectangle, compute its sum of squared deviations from mean, over all color channels.
// see written specification for a description of this function.
double stats::getVar(pair<int,int> ul, int w, int h){
    double ret = 0;
    if (w<1 || h<1) { //might be wrong
        return -999;
    }
    long sumR = getSum('r', ul, w, h);
    long sumG = getSum('g', ul, w, h);
    long sumB = getSum('b', ul, w, h);
    long sumsqR = getSumSq('r', ul, w, h);
    long sumsqG = getSumSq('g', ul, w, h);
    long sumsqB = getSumSq('b', ul, w, h);
    long area = w*h;
    double red = (double)sumsqR - (double)sumR*sumR/area;
    double green = (double)sumsqG - (double)sumG*sumG/area;
    double blue = (double)sumsqB - (double)sumB*sumB/area;
    ret = red+green+blue;
    return abs(ret);
}
		
RGBAPixel stats::getAvg(pair<int,int> ul, int w, int h){
    RGBAPixel ret(0,0,0);
    if (w<1 || h<1) { //might be wrong
        return ret;
    }
    long sumR = getSum('r', ul, w, h);
    long sumG = getSum('g', ul, w, h);
    long sumB = getSum('b', ul, w, h);
    long area = w*h;
    ret.r = (double)sumR/area;
    ret.g = (double)sumG/area;
    ret.b = (double)sumB/area;
    return ret;
}
