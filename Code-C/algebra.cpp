//
//  algebra.cpp
//  Trilight
//
//  Created by Yue on 9/3/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "algebra.h"

Vector operator* (float t, const Vector & a){
    return Vector(t * a.x, t * a.y, t * a.z);
}

 Vector operator- (const Point &a, const Point &b){
     
    return Vector(a.x - b.x, a.y - b.y, a.z - b.z);
}


Point operator+ (const Vector &a, const Point &b){
    return Point(a.x + b.x, a.y + b.y, a.z + b.z);
}

Point operator+ (const Point &b, const Vector &a){
    return Point(a.x + b.x, a.y + b.y, a.z + b.z);
}



