//
//  algebra.cpp
//  Trilight
//
//  Created by Yue on 9/3/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "algebra.h"
#include <math.h>

Vector operator* (float t, const Vector & a){
    return Vector(t * a.x, t * a.y, t * a.z);
}

Vector operator* (const Vector& a,float t){
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

Vector operator* (const Matrix& m, const Vector& vec){
    float *v = m.begin();
    
    float x = vec.x * v[0] + vec.y * v[4] + vec.z* v[8];
    float y = vec.x * v[1] + vec.y * v[5] + vec.z* v[9];
    float z = vec.x * v[2] + vec.y * v[6] + vec.z* v[10];
    
    return Vector(x,y,z);
}

Point operator* (const Matrix&m, const Point &p){
    float *v = m.begin();
    
    float x = p.x * v[0] + p.y * v[4] + p.z* v[8] + v[12];
    float y = p.x * v[1] + p.y * v[5] + p.z* v[9] + v[13];
    float z = p.x * v[2] + p.y * v[6] + p.z* v[10] + v[14];
    
    return Point(x,y,z);
}

Matrix operator* (const Matrix& m, float t){
    float v[16];
    std::copy(m.begin(), m.begin() + 16, v);
    for (int i = 0; i < 16; i++) v[i] *= t;
    
    return Matrix(v);
}