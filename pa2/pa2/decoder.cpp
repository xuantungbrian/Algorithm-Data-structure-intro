#include "decoder.h"
#include "queue.h"
#include "stack.h"
#include <queue>
#include <bits/stdc++.h>
using namespace std;

decoder::decoder(const PNG & tm, pair<int,int> s)
   :start(s),mapImg(tm) {
   vector<vector<bool>> visit;
   vector<vector<int>> len;
   vector<vector<pair<int,int>>> solution;
   queue<pair<int,int>> queue;
   pair<int,int> end;
   pair<int,int> iterator;

   visit.resize(tm.height());
   solution.resize(tm.height());
   len.resize(tm.height());
   for (int i=0; i< (int)tm.height(); i++) { //is there a better way of doing this?
      visit[i].resize(tm.width());
      solution[i].resize(tm.width());
      len[i].resize(tm.width());
      for (int a=0; a< (int)tm.width(); a++) {
         visit[i][a] = false;
      }
   }

   visit[s.second][s.first] = true;
   len[s.second][s.first] = 0;
   queue.push(s);
   
   while (!queue.empty()) {
      pair<int,int> curr = queue.front();
      queue.pop();
      vector<pair<int,int>> neighbours;
      neighbours.resize(4);
      neighbours = neighbors(curr);
      for (int i=0; i<4; i++) {
         if (good(visit, len, curr, neighbours[i])) {
               visit[neighbours[i].second][neighbours[i].first] = true;
               len[neighbours[i].second][neighbours[i].first] = len[curr.second][curr.first] + 1;
               solution[neighbours[i].second][neighbours[i].first] = curr;
               queue.push(neighbours[i]);
         }
      }
      if (queue.empty()) {
         end = curr;
         //cout << "end: " << end.first << "," << end.second << endl;
      }
   }

   iterator = end;
   while (iterator != s) {
      pathPts.push_back(iterator);
      iterator = solution[iterator.second][iterator.first];
   }
   pathPts.push_back(iterator);
   reverse(pathPts.begin(), pathPts.end());
}

PNG decoder::renderSolution(){
   PNG temp = PNG(mapImg);
   for (int i=0; i<(int)pathPts.size(); i++) {
      RGBAPixel* curr = temp.getPixel(pathPts[i].first, pathPts[i].second);
      curr->b = 0;
      curr->g = 0;
      curr->r = 255;
   }
   return temp;
}

PNG decoder::renderMaze(){
   PNG new_image = PNG(mapImg);

   vector<vector<bool>> visit;
   vector<vector<int>> len;
   queue<pair<int,int>> queue;

   visit.resize(new_image.height());
   len.resize(new_image.height());
   for (int i=0; i< (int)new_image.height(); i++) { //is there a better way of doing this?
      visit[i].resize(new_image.width());
      len[i].resize(new_image.width());
      for (int a=0; a< (int)new_image.width(); a++) {
         visit[i][a] = false;
      }
   }

   visit[start.second][start.first] = true;
   len[start.second][start.first] = 0;
   queue.push(start);
   
   while (!queue.empty()) {
      pair<int,int> curr = queue.front();
      queue.pop();
      vector<pair<int,int>> neighbours;
      neighbours.resize(4);
      neighbours = neighbors(curr);
      for (int i=0; i<4; i++) {
         if (good(visit, len, curr, neighbours[i])) {
               visit[neighbours[i].second][neighbours[i].first] = true;
               len[neighbours[i].second][neighbours[i].first] = len[curr.second][curr.first] + 1;
               setGrey(new_image, neighbours[i]);
               queue.push(neighbours[i]);
         }
      }
   }

   for (int x=-3; x<4; x++) {
      for (int y=-3; y<4; y++) {
         int x_val = start.first + x;
         int y_val = start.second + y;
         if (x_val >= 0 && x_val < (int)mapImg.width() && y_val >= 0 && y_val < (int)mapImg.height()) {
               RGBAPixel* red_square = new_image.getPixel(x_val, y_val);
               red_square->r = 255;
               red_square->g = 0;
               red_square->b = 0;
         }
      }
   }
   return new_image;
}

void decoder::setGrey(PNG & im, pair<int,int> loc){
   RGBAPixel* temp = im.getPixel((unsigned int)loc.first, (unsigned int)loc.second);
    temp->r = 2*(temp->r/4);
    temp->g = 2*(temp->g/4);
    temp->b = 2*(temp->b/4);
}

pair<int,int> decoder::findSpot(){
   return pathPts.back();
}

int decoder::pathLength(){
   return abs(pathPts.front().first-pathPts.back().first) + abs(pathPts.front().second-pathPts.back().second);
}

bool decoder::good(vector<vector<bool>> & v, vector<vector<int>> & d, pair<int,int> curr, pair<int,int> next){
   if (next.first >= (int)mapImg.width() || next.second >= (int)mapImg.height() || next.first < 0 || next.second < 0) {
      return false;
   }
   if (v[next.second][next.first] == true) {
      return false;
   }
   RGBAPixel* nextPixel = mapImg.getPixel(next.first, next.second); 
   return compare(nextPixel, d[curr.second][curr.first]+1); // what is an iterator? why erase needs it?
}

vector<pair<int,int>> decoder::neighbors(pair<int,int> curr) {
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


bool decoder::compare(RGBAPixel *p, int d){
   int first_2 = (d%64) >> 4;
   int mid_2 = ((d%64) & 0b001100) >> 2;
   int last_2 = (d%64) & 0b000011;
   int red = p->r & 0b00000011;
   int green = p->g & 0b00000011;
   int blue = p->b & 0b00000011;
   if (red != first_2 || green != mid_2 || blue != last_2) {
      return false;
   }
   else {
      return true;
   }
}
