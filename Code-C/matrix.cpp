//
//  matrix.cpp
//  Code-C
//
//  Created by Yue on 12/6/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "matrix.h"
#include <math.h>

Matrix::Matrix(){
    std::fill(v, v+16, 0.f);
    for (int i = 0; i < 4; i+=1)
        v[4* i + i] = 1.0f;
}

Matrix::Matrix(const Matrix & m){
    std::copy(m.v, m.v+16, v);
}

Matrix::Matrix(float * values){
    std::copy(values, values + 16, v);
}

Matrix::Matrix(Vector c1, Vector c2, Vector c3, Vector c4){
    v[0] = c1.x ; v[4] = c2.x; v[8] = c3.x  ; v[12] = c4.x;
    v[1] = c1.y ; v[5] = c2.y; v[9] = c3.y  ; v[13] = c4.y;
    v[2] = c1.z ; v[6] = c2.z; v[10] = c3.z ; v[14] = c4.z;
    v[3] = 0 ; v[7] = 0; v[11] = 0 ; v[15] = 1;
}

Matrix Matrix::translate(Vector vec){
    return Matrix(Vector(1,0,0), Vector(0,1,0), Vector(0,0,1), vec);
}

Matrix Matrix::roatate(Vector vec, float angle){
    vec.normalize();
    
    float c = cosf(angle * 3.1415926 / 180.0);
    float s = sinf(angle * 3.1415926 / 180.0);
    float x = vec.x; float y = vec.y; float z = vec.z;
    
    v[0] = x*x*(1-c)+c; v[4] = x*y*(1-c)-z*s; v[8] = x*z*(1-c)+y*s; v[12] = 0;
    v[1] = y*x*(1-c)+z*s; v[5] = y*y*(1-c)+c; v[9] = y*z*(1-c)-x*s; v[13] = 0;
    v[2] = x*z*(1-c)-y*s; v[6] = y*z*(1-c)+x*s; v[10] = z*z*(1-c)+c; v[14] = 0;
    v[3] = 0;  v[7] = 0 ;  v[11] = 0;  v[15] = 1;

    return Matrix(v);
}

Matrix Matrix::scale(Vector vec){
    if (vec.x != 0 && vec.y != 0 && vec.z != 0) {
        return Matrix(Vector(vec.x,0,0), Vector(0,vec.y,0), Vector(0,0,vec.z), Vector(0,0,0));
    }else{
        return Matrix();
    }
}

////////////////////////////////////////////////////////////////////////

Matrix& Matrix::operator= (const Matrix & m){
    std::copy(m.v, m.v+16, v);
    return  *this;
}

//Not tested!!
Matrix Matrix::operator *(const Matrix& m){
    float ret[16];
    std::fill(ret, ret + 16, 0.f);
    for (int i = 0; i < 4; i ++) {
        for (int j = 0; j <4 ; j++) {
            for (int c = 0; c < 4; c++) {
                ret[4*i + j] += v[4*i + c] * v[4*j + c];
            }
        }
    }
    return Matrix(ret);
}

std::ostream& operator<< (std::ostream& stream, const Matrix & m){
    for( int i = 0; i < 4; i ++){
        stream<<"[ ";
        for (int j = 0; j < 4; j ++)
            stream<<m.v[4*j + i]<<" ";
        stream<<"]"<<std::endl;
    }
    return stream;
}

float* Matrix::begin() const{
    return (float*)v;
}

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

Matrix Matrix::invert(){
    float inv_out[16];
    if (inverse(v, inv_out)) {
        return Matrix(inv_out);
    }else{
        return *this;
    }
}

//not tested!!!!
Matrix Matrix::transpose(){
    float output[16];
    for (int i = 0; i < 4; i++) {
        for (int j = 0 ; j < 4 ; j++) {
            output[4*i + j] = v[4*j+i];
        }
    }
    
    return Matrix(output);
}