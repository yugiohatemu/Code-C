//
//  vector.cpp
//  Trilight
//
//  Created by Yue on 9/2/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "vector.h"
#include <math.h>
#include <sstream>
#include "utility.h"

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
    if (norm_prod == 0) return 0;
    int angle = (acosf(dot_prod/norm_prod)*180.0 / PI); //asin or acos?
    //should give a errror message
    if (angle > 180  || angle < -180) angle = 0;
    return angle;
}

////////////////////////////////////////////////////////////////////////////////////////
//Static method

//Format (1,2,3)
//Something like that
Vector Vector::get_vector_from_string(std::string s) throw (std::exception){
    
    if ((*s.begin()) == '(' && *(s.end()-1) == ')') { //end and begin is ok
        s.erase(s.begin());
        s.erase(s.end()-1);
    }
  
    //Format is satisfied, now lets strip by comma,
    std::vector<std::string> nums = split(s, ',');
    if (nums.size() != 3) {
        //Throw if # of nums is invalid
        throw ParseError("V:Invalid # of parameters");
    }else{
        //Stringstream to handle error case
        int num[3];
        for (int i = 0; i < nums.size(); i++) {
            //Throw if invalid, use istringstream sees works also for float
            if ( ! (std::istringstream(nums[i]) >> num[i]) ){
                throw ParseError("V:Invalid # format");
            }
        }
        return Vector(num[0],num[1],num[2]);
    }
    
    return Vector();
}

