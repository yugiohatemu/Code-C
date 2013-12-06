//
//  vector.h
//  Trilight
//
//  Created by Yue on 9/2/13.
//  Modified on 29/11/13
//  Copyright (c) 2013 Yue. All rights reserved.
//

#ifndef __Trilight__vector__
#define __Trilight__vector__

#include <iostream>

struct Vector{
    float x, y,z;
    
    Vector();
    Vector(float x, float y,float z);
    Vector(const Vector& vec);
    float dot(Vector vec);
    Vector cross(Vector vec);
    
    Vector operator*(float t);
    Vector operator+(const Vector &vec);
    Vector operator=(const Vector & vec);
    bool operator==(const Vector & vec);
    bool operator!=(const Vector & vec);

    void normalize();
    float get_norm();
    friend std::ostream& operator<< (std::ostream& stream, const Vector& vec);
    
    void set(float x, float y,float z);
    void rotate(char axis, float angel);
    float get_angel_to(Vector vec);
    
};


#endif /* defined(__Trilight__vector__) */
