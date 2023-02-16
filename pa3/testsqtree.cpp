
#define CATCH_CONFIG_MAIN
#include "cs221util/catch.hpp"
#include <iostream>
#include "sqtree.h"

TEST_CASE("sqtree::basic ctor render","[weight=1][part=sqtree]"){
    PNG img;
    img.readFromFile("images/orig/colour.png");
    cout << "image width " << img.width() <<endl;
    cout << "image height " << img.height() <<endl;
    SQtree t1(img); // defaults to tolerance=0.0
    PNG out = t1.render();
    
    REQUIRE(out==img);
}


TEST_CASE("sqtree::basic copy","[weight=1][part=sqtree]"){
    PNG img;
    img.readFromFile("images/orig/colour.png");

    SQtree t1(img);
    SQtree t1copy(t1);

    PNG out = t1copy.render();
    for (int x=0; x<(int)img.width(); x++) {
        for (int y=0; y<(int)img.height(); y++) {
            RGBAPixel *work = out.getPixel(x, y);
            RGBAPixel *ans = img.getPixel(x, y);
            if (*work != *ans) {
                    cout << "wrong color at coordinate x,y = " << x << "," << y << endl;
                    cout << "red: " << (int)work->r << "," << (int)ans->r <<endl;
                    cout << "green: " << (int)work->g << "," << (int)ans->g <<endl;
                    cout << "blue: " << (int)work->b << "," << (int)ans->b <<endl;
            }
        }
    }
    out.writeToFile("images/orig/colour_work.png");
    
    REQUIRE(out==img);
}

TEST_CASE("sqtree::tolerance construction and render","[weight=1][part=sqtree]"){
    PNG img;
    img.readFromFile("images/orig/rocky_bullwinkle.png");
    
    SQtree t1(img,4000.0); 
    PNG result = t1.render();

    // REMOVE FOR TESTING
    //    result.writeToFile("images/soln/rb4000.png");

    PNG expected; 
    expected.readFromFile("images/soln/rb4000.png");

    REQUIRE(expected==result);
}

TEST_CASE("sqtree::size check","[weight=1][part=sqtree]"){
    PNG img;
    img.readFromFile("images/orig/rocky_bullwinkle.png");
    
    SQtree t1(img,4000.0); 
    int result = t1.size();

    // REMOVE FOR TESTING
    //   cerr << "rb4000 size = " << result << endl;

    int expected = 15425;

    REQUIRE(expected==result);
}

TEST_CASE("sqtree::big tolerance construction and render","[weight=1][part=sqtree]"){
    PNG img;
    img.readFromFile("images/orig/van.png");
    
    SQtree t1(img,5590.0);
    PNG result = t1.render();

    // REMOVE FOR TESTING
        result.writeToFile("images/soln/van5590.png");

    PNG expected; 
    expected.readFromFile("images/soln/van5590.png");

    REQUIRE(expected==result);
}

TEST_CASE("sqtree::big size check","[weight=1][part=sqtree]"){
    PNG img;
    img.readFromFile("images/orig/van.png");
    
    SQtree t1(img,5590.0); 
    int result = t1.size();

    // REMOVE FOR TESTING
    // cerr << "van5590 size = " << result << endl;

    int expected = 31755;

    REQUIRE(expected==result);
}


