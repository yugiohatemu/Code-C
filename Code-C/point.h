//
//  point.h
//  from Trilight
//
//  Modified by Yue on 11/29/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#ifndef __Trilight__point__
#define __Trilight__point__
#include <iostream>
#include "parseError.h"

struct Point{
    float x,y,z;
	Point();
	Point(float x, float y,float z);
    Point (const Point &p);

    Point operator*(float s);
    Point operator/(float s);
    Point& operator= (const Point &p);
    bool operator== (const Point &p);
    bool operator!= (const Point &p);
    friend std::ostream& operator<< (std::ostream& stream, const Point& p);
    
    void set(float x, float y,float z);
    void normalize();
    bool is_whithin(Point a, Point b);
    void clamp_angle();
    bool is_within_dis(Point dest, float dis);
    static Point get_mid(Point a, Point b);
    
    static Point get_point_from_string(std::string s) throw (std::exception);
};

#endif /* defined(__Trilight__point__) */
