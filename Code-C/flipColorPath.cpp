//
//  flipColorPath.cpp
//  Code-C
//
//  Created by Yue on 12/22/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "flipColorPath.h"
#include "colorRule.h"
#include "SDL/SDL_opengl.h"

FlipColorPath::FlipColorPath():Path(){
    state = IDLE;
}

FlipColorPath::~FlipColorPath(){
    
}

//////////////////////////////////////////////////////////////////////////////////////////
//Overwrite parent class
Vector FlipColorPath::get_normal(){
    return normal;
}

Matrix FlipColorPath::get_transform(){
    return prod;
}

bool FlipColorPath::is_on_surface(Point p){
    return Path::is_on_surface(p);
}


/////////////////////////////////////////////////////////////////////////////////////////
//Sprite interface
void FlipColorPath::render(){
    //Draw a triangle to differentiate
    glPushMatrix();
    glMultMatrixf(prod.begin());
    glColor4f(c.r, c.g, c.b, c.a);
    glBegin(GL_TRIANGLES);
    glVertex3f(0, 0, -0.5); glVertex3f(0, 0, 0.5); glVertex3f(1, 0, 0);
    glEnd();
    glPopMatrix();
    
    next->render();
}

void FlipColorPath::update(SDL_Event event){
    //can we ask the event to be blocked?
    
    next->update(event);
}

