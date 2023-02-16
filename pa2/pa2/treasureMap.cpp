#include "treasureMap.h"
#include "queue.h"

using namespace std;

treasureMap::treasureMap(const PNG & baseim, const PNG & mazeim, pair<int,int> s)
{
     base = PNG(baseim);
     maze = PNG(mazeim);
     start = s; //need to check this

}

//not sure if invalidate the lower bits have any effects
//also need to ask about the const keyword
void treasureMap::setGrey(PNG & im, pair<int,int> loc)
{
    RGBAPixel* temp = im.getPixel((unsigned int)loc.first, (unsigned int)loc.second);
    temp->r = 2*(temp->r/4);
    temp->g = 2*(temp->g/4);
    temp->b = 2*(temp->b/4);
}

void treasureMap::setLOB(PNG & im, pair<int,int> loc, int d) //does b1b2 of d needs to be binary in red or decimal?
{
    int first_2 = (d%64) >> 4;
    int mid_2 = ((d%64) & 0b001100) >> 2;
    int last_2 = (d%64) & 0b000011;
    RGBAPixel* temp = im.getPixel((unsigned int)loc.first, (unsigned int)loc.second);
    temp->r = (temp->r & 0b11111100) + first_2;
    temp->g = (temp->g & 0b11111100) + mid_2;
    temp->b = (temp->b & 0b11111100) + last_2;
}

PNG treasureMap::renderMap()
{
    PNG temp = PNG(base);
    vector<vector<bool>> visit;
    vector<vector<int>> len;
    queue<pair<int,int>> queue;

    visit.resize(base.height());
    len.resize(base.height());
    for (int i=0; i< (int)base.height(); i++) { //is there a better way of doing this?
        visit[i].resize(base.width());
        len[i].resize(base.width());
        for (int a=0; a< (int)base.width(); a++) {
            visit[i][a] = false;
        }
    }

    /*len.resize(base.height());
    for (int i=0; i< (int)base.height(); i++) { //is there a better way of doing this?
        len[i].resize(base.width());
    }*/

    visit[start.second][start.first] = true;
    len[start.second][start.first] = 0;
    setLOB(temp, start, 0);
    /*RGBAPixel *begin = temp.getPixel(start.first, start.second);
    cout << "start:" << (int)begin->r << "," << (int)begin->g << "," << (int)begin->b <<endl;*/
    queue.push(start);

    while (!queue.empty()) {
        pair<int,int> curr = queue.front();
        queue.pop();
        vector<pair<int,int>> neighbours;
        neighbours.resize(4);
        neighbours = neighbors(curr);
        for (int i=0; i<4; i++) {
            if (good(visit, curr, neighbours[i])) {
                visit[neighbours[i].second][neighbours[i].first] = true;
                len[neighbours[i].second][neighbours[i].first] = len[curr.second][curr.first] + 1;
                setLOB(temp, neighbours[i], len[neighbours[i].second][neighbours[i].first]);
                queue.push(neighbours[i]);
            }
        }
    }

    return temp;
}


PNG treasureMap::renderMaze()
{
    PNG new_image = PNG(base);
    for (int x=0; x< (int)maze.width(); x++) {
        for (int y=0; y< (int)maze.height(); y++) {
            RGBAPixel* temp = maze.getPixel(x, y);
            if (temp->r != 255 || temp->b != 255 || temp->g != 255) { 
                pair<int, int> curr = {x, y};
                setGrey(new_image, curr);
            }
        }
    }
    for (int x=-3; x<4; x++) {
        for (int y=-3; y<4; y++) {
            int x_val = start.first + x;
            int y_val = start.second + y;
            if (x_val >= 0 && x_val < (int)maze.width() && y_val >= 0 && y_val < (int)maze.height()) {
                RGBAPixel* red_square = new_image.getPixel(x_val, y_val);
                red_square->r = 255;
                red_square->g = 0;
                red_square->b = 0;
            }
        }
    }
    return new_image;
}

bool treasureMap::good(vector<vector<bool>> & v, pair<int,int> curr, pair<int,int> next)
{
    if (next.first >= (int)base.width() || next.second >= (int)base.height() || next.first < 0 || next.second < 0) {
        return false;
    }
    if (v[next.second][next.first] == true) {
        return false;
    }
    RGBAPixel* nextPixel = maze.getPixel(next.first, next.second); //is it next within base image?
    RGBAPixel* currPixel = maze.getPixel(curr.first, curr.second);
    if (*nextPixel == *currPixel) {
        return true;
    }
    return false;
}

vector<pair<int,int>> treasureMap::neighbors(pair<int,int> curr)
{
    vector<pair<int,int>> temp; //should I do new vector??
    pair<int,int> left = {curr.first-1, curr.second};
    pair<int,int> below = {curr.first, curr.second+1};
    pair<int,int> right = {curr.first+1, curr.second};
    pair<int,int> above = {curr.first, curr.second-1};
    temp.push_back(left);
    temp.push_back(below);
    temp.push_back(right);
    temp.push_back(above);
    return temp;
}

