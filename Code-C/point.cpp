//
//  point.cpp
//  Trilight
//
//  Created by Yue on 9/2/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "point.h"
#include <math.h>

Point::Point() {
    x = 0.f;
    y = 0.f;
    z = 0.f;
}

Point::Point(float x, float y,float z):x(x),y(y),z(z){
    
}

Point::Point (Point const &p){
    x = p.x;
    y = p.y;
    z = p.z;
}

////////////////////////////////////////////////////
Point Point::operator*(float s){
    return Point(x*s,y*s,z*s);
}

Point Point::operator/(float s){
    if ( s == 0) return *this;
    else return Point(x/s,y/s,z/s);
}

Point& Point::operator= (const Point &p){
    if (this == &p) {
        return *this;
    }
    x = p.x;
    y = p.y;
    z = p.z;
    return *this;
}

bool Point::operator== (const Point &p){
    return x == p.x && y == p.y && z == p.z;
}

bool Point::operator!= (const Point &p){
    return x != p.x || y != p.y || z !=p.z;
}

std::ostream& operator<< (std::ostream& stream, const Point& p){
    stream<<"[POT] ("<<p.x<<","<<p.y<<","<<p.z<<")";
    return stream;
}

////////////////////////////////////////////////////
//dot multiply
float Point::dot(Point p){
    return x*p.x + y*p.y + z*p.z;
}


void Point::normalize(){
    float n = sqrt(x*x + y*y + z*z);
    if (n != 0 ){
        x = x/n;
        y = y/n;
        z = z/n;
    }
}

