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

Protagonist::Protagonist(){
    
}

Protagonist::~Protagonist(){
    
}

void Protagonist::render(){
    glPushMatrix();

    glTranslatef(anchor.x, anchor.y, anchor.z);
    glColor3f(1.0, 1.0, 0);
    glutSolidCube(0.5);
    
    glPopMatrix();
}

void Protagonist::update(SDL_Event event){
    float speed = 0.1f;
    if (event.type == SDL_KEYDOWN) {
    
        if(event.key.keysym.sym == SDLK_UP) anchor.z -= speed;
        if(event.key.keysym.sym == SDLK_DOWN) anchor.z += speed;
        if(event.key.keysym.sym == SDLK_LEFT) anchor.x -= speed;
        if(event.key.keysym.sym == SDLK_RIGHT) anchor.x += speed;
    }
}