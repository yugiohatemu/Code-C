//
//  point.cpp
//  Trilight
//
//  Created by Yue on 9/2/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "point.h"
#include <math.h>
#include "utility.h"

Point::Point() {
    x = 0.f;
    y = 0.f;
    z = 0.f;
}

Point::Point(float x, float y,float z):x(x),y(y),z(z){
    
}

Point::Point (const Point &p){
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

void Point::set(float x, float y,float z){
    this->x = x;
    this->y = y;
    this->z = z;
}

void Point::normalize(){
    float n = sqrt(x*x + y*y + z*z);
    if (n != 0 ){
        x = x/n;
        y = y/n;
        z = z/n;
    }
}

bool Point::is_within_dis(Point dest, float dis){
    float f = sqrtf( (x - dest.x)*(x - dest.x) + (y -dest.y)*(y -dest.y) + (z - dest.z) * (z - dest.z));
    return f<=dis;
}

bool Point::is_whithin(Point a, Point b){
    return is_num_whithin(x, a.x, b.x) && is_num_whithin(y, a.y, b.y) && is_num_whithin(z, a.z, b.z);
}

void Point::clamp_angle(){
    //0 to 180, >= 90, we set it to 9
    if (x >= 90) x = 0;
    if (y >= 90) y = 0;
    if (z >= 90) z = 0;
}

Point Point::get_mid(Point a, Point b){
    return Point(a.x + b.x, a.y + b.y, a.z + b.z) * 0.5f;
}
