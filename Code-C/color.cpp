//
//  color.cpp
//  Code-C
//
//  Created by Yue on 11/29/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "color.h"


Color::Color(float r, float g,float b,float a):r(r),g(g),b(b), a(a){
    //avoid nasty outcome
    if (r > 1.0f || r < 0.0f) r = 1.0f;
    if (g > 1.0f || g < 0.0f) g = 1.0f;
    if (b > 1.0f || b < 0.0f) b = 1.0f;
    if (a > 1.0f || a < 0.0f) a = 1.0f;
    
}

Color::Color(float c){
    if (c > 1.0f || c < 0.0f) c = 1.0f;
    r = g = b = a = c;
}

Color::Color(const Color & c){
    this->r = c.r;
    this->g = c.g;
    this->b = c.b;
    this->a = c.a;
}

Color& Color::operator=(const Color& c){
    this->r = c.r;
    this->g = c.g;
    this->b = c.b;
    this->a = c.a;
    return *this;
}