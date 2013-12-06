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

 Vector operator- (const Point &a, const Point &b){
     
    return Vector(a.x - b.x, a.y - b.y, a.z - b.z);
}


Point operator+ (const Vector &a, const Point &b){
    return Point(a.x + b.x, a.y + b.y, a.z + b.z);
}

Point operator+ (const Point &b, const Vector &a){
    return Point(a.x + b.x, a.y + b.y, a.z + b.z);
}

//Borrowed from a Linux graphic library
bool inverse(float *m, float *invOut){
    float inv[16], det;

    inv[0] = m[5]  * m[10] * m[15] -
    m[5]  * m[11] * m[14] -
    m[9]  * m[6]  * m[15] +
    m[9]  * m[7]  * m[14] +
    m[13] * m[6]  * m[11] -
    m[13] * m[7]  * m[10];
    
    inv[4] = -m[4]  * m[10] * m[15] +
    m[4]  * m[11] * m[14] +
    m[8]  * m[6]  * m[15] -
    m[8]  * m[7]  * m[14] -
    m[12] * m[6]  * m[11] +
    m[12] * m[7]  * m[10];
    
    inv[8] = m[4]  * m[9] * m[15] -
    m[4]  * m[11] * m[13] -
    m[8]  * m[5] * m[15] +
    m[8]  * m[7] * m[13] +
    m[12] * m[5] * m[11] -
    m[12] * m[7] * m[9];
    
    inv[12] = -m[4]  * m[9] * m[14] +
    m[4]  * m[10] * m[13] +
    m[8]  * m[5] * m[14] -
    m[8]  * m[6] * m[13] -
    m[12] * m[5] * m[10] +
    m[12] * m[6] * m[9];
    
    inv[1] = -m[1]  * m[10] * m[15] +
    m[1]  * m[11] * m[14] +
    m[9]  * m[2] * m[15] -
    m[9]  * m[3] * m[14] -
    m[13] * m[2] * m[11] +
    m[13] * m[3] * m[10];
    
    inv[5] = m[0]  * m[10] * m[15] -
    m[0]  * m[11] * m[14] -
    m[8]  * m[2] * m[15] +
    m[8]  * m[3] * m[14] +
    m[12] * m[2] * m[11] -
    m[12] * m[3] * m[10];
    
    inv[9] = -m[0]  * m[9] * m[15] +
    m[0]  * m[11] * m[13] +
    m[8]  * m[1] * m[15] -
    m[8]  * m[3] * m[13] -
    m[12] * m[1] * m[11] +
    m[12] * m[3] * m[9];
    
    inv[13] = m[0]  * m[9] * m[14] -
    m[0]  * m[10] * m[13] -
    m[8]  * m[1] * m[14] +
    m[8]  * m[2] * m[13] +
    m[12] * m[1] * m[10] -
    m[12] * m[2] * m[9];
    
    inv[2] = m[1]  * m[6] * m[15] -
    m[1]  * m[7] * m[14] -
    m[5]  * m[2] * m[15] +
    m[5]  * m[3] * m[14] +
    m[13] * m[2] * m[7] -
    m[13] * m[3] * m[6];
    
    inv[6] = -m[0]  * m[6] * m[15] +
    m[0]  * m[7] * m[14] +
    m[4]  * m[2] * m[15] -
    m[4]  * m[3] * m[14] -
    m[12] * m[2] * m[7] +
    m[12] * m[3] * m[6];
    
    inv[10] = m[0]  * m[5] * m[15] -
    m[0]  * m[7] * m[13] -
    m[4]  * m[1] * m[15] +
    m[4]  * m[3] * m[13] +
    m[12] * m[1] * m[7] -
    m[12] * m[3] * m[5];
    
    inv[14] = -m[0]  * m[5] * m[14] +
    m[0]  * m[6] * m[13] +
    m[4]  * m[1] * m[14] -
    m[4]  * m[2] * m[13] -
    m[12] * m[1] * m[6] +
    m[12] * m[2] * m[5];
    
    inv[3] = -m[1] * m[6] * m[11] +
    m[1] * m[7] * m[10] +
    m[5] * m[2] * m[11] -
    m[5] * m[3] * m[10] -
    m[9] * m[2] * m[7] +
    m[9] * m[3] * m[6];
    
    inv[7] = m[0] * m[6] * m[11] -
    m[0] * m[7] * m[10] -
    m[4] * m[2] * m[11] +
    m[4] * m[3] * m[10] +
    m[8] * m[2] * m[7] -
    m[8] * m[3] * m[6];
    
    inv[11] = -m[0] * m[5] * m[11] +
    m[0] * m[7] * m[9] +
    m[4] * m[1] * m[11] -
    m[4] * m[3] * m[9] -
    m[8] * m[1] * m[7] +
    m[8] * m[3] * m[5];
    
    inv[15] = m[0] * m[5] * m[10] -
    m[0] * m[6] * m[9] -
    m[4] * m[1] * m[10] +
    m[4] * m[2] * m[9] +
    m[8] * m[1] * m[6] -
    m[8] * m[2] * m[5];
    
    //if the matrix is not invertable
    det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];
    
    if (det == 0) return false;
    
    det = 1.0 / det;
    
    for (int i = 0; i < 16; i++)
        invOut[i] = inv[i] * det;
    
    return true;
}

void onelize(Vector vec){
    //only used in find basis matrix since we dont want to scale the unit or someing
    
}

float* basis_matrix(Vector x, Vector y, Vector z, Point o){
    float matrix[16];
    //here I want to add an additional normalize
    //make them to be 1 because no unit addition is changed, right?
    matrix[0] = x.x; matrix[4] = y.x ; matrix[8] = z.x; matrix[12] = o.x;
    matrix[1] = x.y; matrix[5] = y.y ; matrix[9] = z.y; matrix[13] = o.y;
    matrix[2] = x.z; matrix[6] = y.z ; matrix[10] = z.z; matrix[14] = o.z;
    matrix[3] = 0;  matrix[7] = 0 ;  matrix[11] = 0;  matrix[15] = 1;

    float * inv_matrix = new float [16];
    
//    for (int i = 0; i < 16; i+=1) inv_matrix[i] = matrix[i];
    if (!inverse(matrix, inv_matrix)) {
        for (int i = 0; i < 16; i+=1) inv_matrix[i] = 0;
        for (int i = 0; i < 4; i+=1) inv_matrix[4*i + i] = 1;
    }else{
        //normalize the matrix!!!
        for (int i = 0; i < 3; i+=1) {
            Vector vec(inv_matrix[4*i], inv_matrix[4*i+1],inv_matrix[4*i+2]);
            vec.normalize();
            inv_matrix[4*i] = vec.x;
            inv_matrix[4*i + 1] = vec.y;
            inv_matrix[4*i + 2] = vec.z;
        }
    }
    return inv_matrix;
}

float * rotation_matrix(float angle, float x, float y , float z){
    float * matrix = new float[16];
    float c = cosf(angle * 3.1415926/ 180.0);
    float s = sinf(angle * 3.1415926 / 180.0);
    
    matrix[0] = x*x*(1-c)*c; matrix[4] = x*y*(1-c)-z*s; matrix[8] = x*z*(1-c)+y*s; matrix[12] = 0;
    matrix[1] = y*x*(1-c)+z*s; matrix[5] = y*y*(1-c)+c; matrix[9] = y*z*(1-c)-x*s; matrix[13] = 0;
    matrix[2] = x*z*(1-c)-y*s; matrix[6] = y*z*(1-c)+x*s; matrix[10] = z*z*(1-c)+c; matrix[14] = 0;
    matrix[3] = 0;  matrix[7] = 0 ;  matrix[11] = 0;  matrix[15] = 1;
    
    return matrix;
}

float * rotation_matrix(float angle, Vector vec){
    vec.normalize();
    return rotation_matrix(angle, vec.x, vec.y, vec.z);
}
