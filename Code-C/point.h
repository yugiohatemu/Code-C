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

struct Point{
    float x,y,z;
	Point();
	Point(float x, float y,float z);
    Point (Point const &p);

    Point operator*(float s);
    Point operator/(float s);
    Point& operator= (const Point &p);
    bool operator== (const Point &p);
    bool operator!= (const Point &p);
    friend std::ostream& operator<< (std::ostream& stream, const Point& p);
    
    void normalize();
    float dot(Point p);
    //float cross(Point p);
};

#endif /* defined(__Trilight__point__) */
