//
//  point.cpp
//  Trilight
//
//  Created by Yue on 9/2/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "point.h"
#include <math.h>
#include <sstream>
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

Point Point::get_point_from_string(std::string s) throw (std::exception){
    if ((*s.begin()) == '(' && *(s.end()-1) == ')') { //end and begin is ok
        s.erase(s.begin());
        s.erase(s.end()-1);
    }
    
    //Format is satisfied, now lets strip by comma,
    std::vector<std::string> nums = split(s, ',');
    if (nums.size() != 3) {
        //Throw if # of nums is invalid
        throw ParseError("P:Invalid # of parameters");
    }else{
        //Stringstream to handle error case
        int num[3];
        for (int i = 0; i < nums.size(); i++) {
            //Throw if invalid, use istringstream sees works also for float
            if ( ! (std::istringstream(nums[i]) >> num[i]) ){
                throw ParseError("P:Invalid # format");
            }
        }
        return Point(num[0],num[1],num[2]);
    }
    
    return Point();
}
