#define CATCH_CONFIG_MAIN

#include <iostream>
#include <limits.h>
#include <sys/stat.h>
#include <vector>

#include "cs221util/RGBAPixel.h"
#include "cs221util/PNG.h"
#include "cs221util/catch.hpp"

#include "decoder.h"
#include "treasureMap.h"

using namespace std;
using namespace cs221util;

#define IMAGEDIR "images/"
#define SOLNIMGDIR "soln_images/"

/**
 * Test Cases
 * these are just examples of a logical flow similar to 
 * that of main.cpp. We suggest decoupling the embedding
 * tests from the decoding tests, but we leave it to you
 * to do so.
 */

TEST_CASE("treasureMap::basic no cycles", "[weight=1][part=treasureMap]")
{

	PNG maze;
	maze.readFromFile("images/snake.png");
	pair<int,int> start(1,1);

    PNG base;
    base.readFromFile("images/sunshine.png");

    treasureMap M(base, maze, start);
    
    PNG treasure = M.renderMap();
	treasure.writeToFile("images/embeddedsnake_work.png");
    PNG treasureans;
    treasureans.readFromFile("images/embeddedsnake.png");
    /*for (int x=0; x<(int)treasureans.width(); x++) {
        for (int y=0; y<(int)treasureans.height(); y++) {
            RGBAPixel *work = treasure.getPixel(x, y);
            RGBAPixel *ans = treasureans.getPixel(x, y);
            RGBAPixel *red = maze.getPixel(x,y);
            RGBAPixel *org = base.getPixel(x,y);
            if (*work != *ans) {
                    if (red->r == 255) {
                        cout << "wrong maze path at coordinate x,y" << x << "," << y << endl;
                    }
                    cout << "wrong color at coordinate x,y = " << x << "," << y << endl;
                    cout << "red: " << (int)org->r << "," << (int)work->r << "," << (int)ans->r <<endl;
                    cout << "green: " << (int)org->g << "," << (int)work->g << "," << (int)ans->g <<endl;
                    cout << "blue: " << (int)org->b << "," << (int)work->b << "," << (int)ans->b <<endl;
                    break;
            }
        }
        break;
    }*/
    REQUIRE( treasure == treasureans );
    
    PNG treasuremaze = M.renderMaze();
	treasuremaze.writeToFile("images/greyedsnake_work.png");

    PNG treasuremazeans;
	treasuremazeans.readFromFile("images/greyedsnake.png");
    
    REQUIRE( treasuremaze == treasuremazeans );


    
    decoder dec(treasure,start);

    PNG soln = dec.renderSolution();
    soln.writeToFile("images/solnsnake_work.png");
    PNG solnans;
    solnans.readFromFile("images/solnsnake.png");
    for (int x=0; x<(int)treasureans.width(); x++) {
        for (int y=0; y<(int)treasureans.height(); y++) {
            RGBAPixel *work = treasure.getPixel(x, y);
            RGBAPixel *ans = treasureans.getPixel(x, y);
            if (*work != *ans) {
                    cout << "wrong color at coordinate x,y = " << x << "," << y << endl;
                    cout << "red: " << (int)work->r << "," << (int)ans->r <<endl;
                    cout << "green: " << (int)work->g << "," << (int)ans->g <<endl;
                    cout << "blue: " << (int)work->b << "," << (int)ans->b <<endl;
                    break;
            }
        }
        break;
    }
    REQUIRE( soln == solnans );

    PNG solnmaze = dec.renderMaze();
    //solnmaze.writeToFile("images/solnsnakemaze.png");
    PNG solnmazeans;
    solnmazeans.readFromFile("images/solnsnakemaze.png");
    REQUIRE( solnmaze == solnmazeans );

}


TEST_CASE("decoder::basic cycles", "[weight=1][part=decoder]")
{
	PNG maze;
	maze.readFromFile("images/maze.png");
	pair<int,int> start(1,1);

    PNG base;
    base.readFromFile("images/sunshine.png");

    treasureMap M(base, maze, start);

    PNG treasure = M.renderMap();
	//treasure.writeToFile("images/embeddedmaze.png");
    PNG treasureans;
    treasureans.readFromFile("images/embeddedmaze.png");
    REQUIRE( treasure == treasureans );

    PNG treasuremaze = M.renderMaze();
	//treasuremaze.writeToFile("images/greyedmaze.png");
    PNG treasuremazeans;
	treasuremazeans.readFromFile("images/greyedmaze.png");
    REQUIRE( treasuremaze == treasuremazeans );

    
    decoder dec(treasure,start);

    PNG soln = dec.renderSolution();
    //soln.writeToFile("images/solnmaze.png");
    PNG solnans;
    solnans.readFromFile("images/solnmaze.png");
    REQUIRE( soln == solnans );

    PNG solnmaze = dec.renderMaze();
    //solnmaze.writeToFile("images/solnmazemaze.png");
    PNG solnmazeans;
    solnmazeans.readFromFile("images/solnmazemaze.png");
    REQUIRE( solnmaze == solnmazeans );

}

