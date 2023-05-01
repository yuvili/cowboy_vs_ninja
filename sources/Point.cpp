#include <bits/stdc++.h>
#include "Point.hpp"
using namespace std;

Point::Point() : _x(0.0), _y(0.0) {}

Point::Point(double x, double y) : _x(x), _y(y) {}

Point::~Point(){} // Destructor

// Copy constructor
Point::Point(const Point& other) : _x(other._x), _y(other._x) {}

Point::Point(Point&& other) noexcept{} // Move constructor

double Point::distance(Point& point2){
    return sqrt(pow(point2.getX() - _x, 2) + pow(point2.getY() - _y, 2) * 1.0);
}

void Point::print(){
    cout << "(" << _x << "," << _y << ")" << endl;
}

Point& Point::moveTowards(Point& src, Point& dest, double distance){

}

double Point::getX(){
    return _x;
}

double Point::getY(){
    return _y;
}