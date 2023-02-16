#include "block.h"
#include <cmath>
#include <iostream>

int Block::width() const
{
    return data[0].size();
}
int Block::height() const
{
    return data.size();
}

void Block::render(PNG &im, int column, int row) const //why const here?
{
    int width = data[0].size();
    int height = data.size();

    for (int x=0; x < height; x++) { //does the PNG starts at 0?
        for (int y=0; y < width; y++) {
            RGBAPixel *im_pixel = im.getPixel(y+column, x+row);
            im_pixel->r = data[x][y].r ;
            im_pixel->g = data[x][y].g ;
            im_pixel->b = data[x][y].b ;
            im_pixel->a = data[x][y].a ;
        }
    } 
}

void Block::build(PNG &im, int column, int row, int width, int height)
{   
    //maybe i need to check if the block fit the image
    //will the block is upside down or up?
    data.resize(height);
    for (int x=row; x < row+height; x++) { //does the PNG starts at 0?
        data[x-row].resize(width);
        for (int y=column; y < column+width; y++) {
            RGBAPixel *im_pixel = im.getPixel(y,x);
            data[x-row][y-column].r = im_pixel->r;
            data[x-row][y-column].g = im_pixel->g;
            data[x-row][y-column].b = im_pixel->b; 
            data[x-row][y-column].a = im_pixel->a;
        }
    } 
}

void Block::flipVert()
{
    int width = data[0].size();
    int height = data.size();

    for (int x=0; x < (int) height/2; x++) { //does the PNG starts at 0?
        for (int y=0; y < width; y++) {
            RGBAPixel temp = data[x][y];
            data[x][y] = data[height-x-1][y];
            data[height-x-1][y] = temp;
        }
    }
}

void Block::flipHoriz()
{
    int width = data[0].size();
    int height = data.size();

    for (int x=0; x < height; x++) { //does the PNG starts at 0?
        for (int y=0; y < (int) width/2; y++) {
            RGBAPixel temp = data[x][y];
            data[x][y] = data[x][width-y-1];
            data[x][width-y-1] = temp;
        }
    }
}

void Block::rotateRight() //how to put an object into its own function?
{
    int width = data[0].size();
    int height = data.size();
    vector<vector<RGBAPixel>> copy;
    copy.resize(height); //not sure about vector, do they have an element at first? If not, why i can resize the width?

    for (int x=0; x < height; x++) { //does the PNG starts at 0? 
            copy[x].resize(width); 
    } 

    if (width != height) {
        cout << "WARNING: rotateRight does not receive a square" << endl; // is this the right thing to do?
        return;
    }

    //divide the block into 4 smaller pieces. Copy the first block. Then copy the lower left to the first one. Then do the all 4.
    for (int x=0; x < (int) height/2; x++) { //does the PNG starts at 0? 
        for (int y=0; y < (int) width/2; y++) { //be careful with the bound (int) width/2
            copy[x][y] = data[x][y];  
        }
    } 

    for (int x=0; x < (int) height/2; x++) { //does the PNG starts at 0? 
        for (int y=0; y < (int) width/2; y++) { //be careful with the bound (int) width/2
            data[x][y] = data[height-x-1][y];  
        }
    } 

    for (int x = (int)(height+1)/2; x < height; x++) { //does the PNG starts at 0? 
        for (int y=0; y < (int) width/2; y++) { //be careful with the bound (int) width/2
            data[x][y] = data[x][width-y-1];  
        }
    } 

    for (int x = (int)(height+1)/2; x < height; x++) { //does the PNG starts at 0? 
        for (int y = (int)(width+1)/2; y < width; y++) { //be careful with the bound (int) width/2
            data[x][y] = data[height-x-1][y];  
        }
    } 

    for (int x=0; x < (int) height/2; x++) { 
        for (int y=(int) (width+1)/2; y < width; y++) { //be careful with the bound (int) width/2
            data[x][y] = copy[x][width-y-1];  
        }
    } 
    if (width%2 == 1) {
        RGBAPixel temp = data[0][(int)width/2];
        data[0][(int)width/2] = data[(int)width/2][0];
        data[(int)width/2][0] = data[width-1][(int)width/2];
        data[width-1][(int)width/2] = data[(int)width/2][width-1];
        data[(int)width/2][width-1] = temp;

    }
}
