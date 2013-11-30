//
//  vector.cpp
//  Trilight
//
//  Created by Yue on 9/2/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "vector.h"
#include <math.h>
#define PI 3.14159265

Vector::Vector(){
    x = 0.f;
    y = 0.f;
    z = 0.f;
}

Vector::Vector(float x, float y, float z):x(x), y(y), z(z){
    
}

Vector::Vector(const Vector &vec){
    x = vec.x;
    y = vec.y;
    z = vec.z;
}

Vector Vector::operator*(float t){
    return Vector(t*x,t*y,t*z);
}

Vector Vector::operator+(const Vector &vec){
    return Vector(x + vec.x, y + vec.y, z + vec.z);
}

Vector Vector::operator=(const Vector & vec){
    x = vec.x;
    y = vec.y;
    z = vec.z;
    return *this;
}

bool Vector::operator==(const Vector & vec){
    return x == vec.x && y == vec.y && z == vec.z;
}

bool Vector::operator!=(const Vector & vec){
    return x != vec.x || y != vec.y || z != vec.z;
}

std::ostream& operator<< (std::ostream& stream, const Vector& vec){
    stream<<"[VEC] ["<<vec.x<<","<<vec.y<<","<<vec.z<<"]";
    return stream;
}

//////////////////////////////////
Vector Vector::normalize(){
    float n = get_norm();
    if (n != 0) {
        return Vector(x/n, y/n,z/n);
    }else{
        return Vector(); //must be 0 0 then
    }
}

float Vector::get_norm(){
    return sqrtf(x*x + y*y+ z*z);
}

float Vector::dot(Vector vec){
    return x * vec.x + y * vec.y + z * vec.z;
}

Vector Vector::cross(Vector vec){
    return Vector(y * vec.z - z * vec.y, z * vec.x - x * vec.z, x * vec.y - y * vec.x);
}

void Vector::set(float x, float y,float z){
    this->x = x;
    this->y = y;
    this->z = z;
}
//float Vector::get_angel(){
//    return atan2f (y,x) * 180 / PI;
//}
//Vector Vector::rotate(float angel){
//    angel = angel * PI / 180;
//    float cos_angel = cosf(angel);
//    float sin_angel = sinf(angel);
//    //[cos -sin ][x]
//    //[sin cos  ][y]
//    return Vector(cos_angel * x - sin_angel * y, sin_angel * x + cos_angel * y );
//}
//
////////////////////////////////////////////
//bool is_vector_parallel(Vector a, Vector b){
//    return a.cross(b) == 0;
//}
//
//Vector get_perpendicular(Vector a){
//    return Vector(-a.y, a.x);
//}

