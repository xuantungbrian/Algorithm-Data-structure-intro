/**
 *
 * shifty quadtree (pa3)
 * sqtree.cpp
 * This file will be used for grading.
 *
 */

#include "sqtree.h"
#include <iostream>
#include <float.h>

// First Node constructor, given.
SQtree::Node::Node(pair<int,int> ul, int w, int h, RGBAPixel a, double v)
  :upLeft(ul),width(w),height(h),avg(a),var(v),NW(NULL),NE(NULL),SE(NULL),SW(NULL)
{}

// Second Node constructor, given
SQtree::Node::Node(stats & s, pair<int,int> ul, int w, int h)
  :upLeft(ul),width(w),height(h),NW(NULL),NE(NULL),SE(NULL),SW(NULL) {
  avg = s.getAvg(ul,w,h);
  var = s.getVar(ul,w,h);
}

// SQtree destructor, given.
SQtree::~SQtree() {
  clear();
}

// SQtree copy constructor, given.
SQtree::SQtree(const SQtree & other) {
  copy(other);
}

// SQtree assignment operator, given.
SQtree & SQtree::operator=(const SQtree & rhs) {
  if (this != &rhs) {
    clear();
    copy(rhs);
  }
  return *this;
}

/**
 * SQtree constructor given tolerance for variance.
 */
SQtree::SQtree(PNG & imIn, double tol) {
  stats s(imIn);
  pair<int,int> start({0,0});
  int w = imIn.width();
  int h = imIn.height();
  root = buildTree(s, start, w, h, tol);
}

/**
 * Helper for the SQtree constructor.
 */
SQtree::Node * SQtree::buildTree(stats & s, pair<int,int> & ul, int w, int h, double tol) {
  if (w == 1 && h == 1) {
    Node *temp = new Node(ul, w, h, s.getAvg(ul, w, h), s.getVar(ul, w, h));
    temp->NW = NULL;
    temp->NE = NULL;
    temp->SW = NULL;
    temp->SE = NULL;
    return temp;
  }
  else if (w < 1 || h < 1) {
    return NULL;
  }
  else if (s.getVar(ul, w, h) < tol) { // may need =
    Node *temp = new Node(ul, w, h, s.getAvg(ul, w, h), s.getVar(ul, w, h));
    temp->NW = NULL;
    temp->NE = NULL;
    temp->SW = NULL;
    temp->SE = NULL;
    return temp;
  }
  else {
    double minimum = DBL_MAX;
    pair<int,int> temp2({0,0});
    double maximumOf4;
    pair<int,int> nw = ul;
    pair<int,int> ne({0,0});
    pair<int,int> sw({0,0});
    pair<int,int> se({0,0});
    Node *temp = new Node(ul, w, h, s.getAvg(ul, w, h), s.getVar(ul, w, h));
    for (int x=0; x<w; x++) {
      for (int y=0; y<h; y++) {
        if (x == 0 && y == 0) {

        }
        else {
          ne.first = ul.first+x;
          ne.second = ul.second;
          sw.first = ul.first;
          sw.second = ul.second+y;
          se.first = ul.first+x;
          se.second = ul.second+y;
          maximumOf4 = max(s.getVar(nw, x, y),s.getVar(ne, w-x, y), s.getVar(sw, x, h-y), s.getVar(se, w-x, h-y));
          if (minimum>=maximumOf4) {
            minimum = maximumOf4;
            temp2.first = x;
            temp2.second = y;
          }
        }
      }
    }
    ne.first = ul.first+temp2.first;
    ne.second = ul.second;
    sw.first = ul.first;
    sw.second = ul.second+temp2.second;
    se.first = ul.first+temp2.first;
    se.second = ul.second+temp2.second;
    temp->NW = buildTree(s, nw, temp2.first, temp2.second, tol);
    temp->NE = buildTree(s, ne, w-temp2.first, temp2.second, tol);
    temp->SW = buildTree(s, sw, temp2.first, h-temp2.second, tol);
    temp->SE = buildTree(s, se, w-temp2.first, h-temp2.second, tol);
    return temp;
  }
}
  
/**
 * Render SQtree and return the resulting image.
 */
PNG SQtree::render() {
  PNG ret(root->width, root->height);
  color(ret, root);
  return ret;
}

/**
 * Delete allocated memory.
 */
void SQtree::clear() {
  destroy(root);
}

void SQtree::copy(const SQtree & other) {
  draw(root, other.root);
}

int SQtree::size() {
  int sum = 0;
  count(root, sum);
  return sum;
}

void SQtree::count(Node *ptr, int &sum) {
  if (ptr!=NULL) {
    count(ptr->NW, sum);
    count(ptr->NE, sum);
    count(ptr->SW, sum);
    count(ptr->SE, sum);
    sum++;
  }
}

void SQtree::destroy(Node *&ptr) {
  if (ptr!=NULL) {
    destroy(ptr->NW);
    destroy(ptr->NE);
    destroy(ptr->SW);
    destroy(ptr->SE);
    delete ptr;
    ptr = NULL;
  }
}
void SQtree::color(PNG &png, Node *ptr) {
  if (ptr != NULL) {
    int w = ptr->width;
    int h = ptr->height;
    for (int x=ptr->upLeft.first; x<ptr->upLeft.first+w; x++) {
      for (int y=ptr->upLeft.second; y<ptr->upLeft.second+h; y++) {
        RGBAPixel *temp = png.getPixel(x, y);
        temp->r = ptr->avg.r;
        temp->g = ptr->avg.g;
        temp->b = ptr->avg.b;
        temp->a = ptr->avg.a;
      }
    }
    color(png, ptr->NW);
    color(png, ptr->NE);
    color(png, ptr->SW);
    color(png, ptr->SE);
  }
}

void SQtree::draw(Node *&node, Node *other_node) {
  if (other_node!=NULL) {
   node = new Node(other_node->upLeft, other_node->width, other_node->height, other_node->avg, other_node->var);
   draw(node->NW, other_node->NW);
   draw(node->NE, other_node->NE);
   draw(node->SW, other_node->SW);
   draw(node->SE, other_node->SE);
  }
}

double SQtree::max(double a, double b, double c, double d) {
  double ret = a;
  if (ret < b) {
    ret = b;
  }
  if (ret < c) {
    ret = c;
  }
  if (ret < d) {
    ret = d;
  }
  return ret;
}

