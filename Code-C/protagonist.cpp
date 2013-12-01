//
//  protagonist.cpp
//  Code-C
//
//  Created by Yue on 11/28/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "protagonist.h"
#include "SDL/SDL_opengl.h"
#include <GLUT/GLUT.h>
#include "camera.h"

Protagonist::Protagonist(){
    
}

Protagonist::~Protagonist(){
    
}

void Protagonist::render(){
    glPushMatrix();

    glTranslatef(anchor.x, anchor.y, anchor.z);
    glColor3f(0, 0, 1.0);
    glutSolidCube(0.5);
    
    glPopMatrix();
}

void Protagonist::update(SDL_Event event){
    float speed = 0.1f;
    //movement vector is based on global orientation
    
    if (event.type == SDL_KEYDOWN) {
        Vector dir = Camera::Instance().get_direction(event.key.keysym.sym) * speed;
        anchor = anchor + dir;
    }
}

Point Protagonist::get_anchor(){
    return anchor;
}