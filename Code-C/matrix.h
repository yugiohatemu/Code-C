//
//  matrix.h
//  Code-C
//
//  Created by Yue on 12/6/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#ifndef __Code_C__matrix__
#define __Code_C__matrix__

//a 4 x 4 matrix with opengl format
#include "vector.h"
#include <iostream>
#include "point.h"
class Matrix{
    float v[16];
public:
    Matrix();
    Matrix(const Matrix & m);
    Matrix(float * values);
    Matrix(Vector c1, Vector c2, Vector c3, Vector c4);
    static Matrix translate(Vector vec);
    static Matrix translate(Point p);
    static Matrix rotate(Vector vec, float angle);
    static Matrix scale(Vector vec);
    static Matrix rotateXYZ(Vector vec);
    
    Matrix& operator= (const Matrix & m);
    Matrix operator *(const Matrix& m);
    friend std::ostream& operator<< (std::ostream& stream, const Matrix & m);
    
    float* begin() const;
    Matrix invert();
    Matrix transpose();
    
};



#endif /* defined(__Code_C__matrix__) */
