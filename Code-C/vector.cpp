//
//  vector.cpp
//  Trilight
//
//  Created by Yue on 9/2/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "vector.h"
#include <math.h>
#define PI 3.1415

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
void Vector::normalize(){
    float n = get_norm();
    if (n != 0) {
        x = x/n;
        y = y/n;
        z = z/n;
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


void Vector::rotate(char axis, float angel){
    angel = angel * PI / 180.0;
    float cos_angel = cosf(angel);
    float sin_angel = sinf(angel);

    float nx, ny, nz = 0.0f;
    switch (axis) {
        case 'x':case 'X':
            ny = cos_angel * y - sin_angel * z;
            nz = sin_angel * y + cos_angel * z;
            y = ny; z = nz;
            break;
        case 'y':case 'Y':
            nx = cos_angel * x - sin_angel * z;
            nz = sin_angel * x + cos_angel * z;
            x = nx; z = nz;
            break;
        case 'z':case 'Z':
            nx = cos_angel * x - sin_angel * y;
            ny = sin_angel * x + cos_angel * y;
            x = nx; y = ny;
            break;
        default:
            break;
    }

}
float Vector::get_angel_to(Vector vec){
    float dot_prod = dot(vec);
    float norm_prod = get_norm() * vec.get_norm();
    //shouldnt be 0 anyway
    if (norm_prod == 0) return 0; //should give a errror message
    else return acosf(dot_prod/norm_prod);
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

