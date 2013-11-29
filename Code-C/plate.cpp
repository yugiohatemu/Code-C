//
//  plate.cpp
//  Code-C
//
//  Created by Yue on 11/29/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "plate.h"
#include "SDL/SDL_opengl.h"

void Plate::render(){
    glPushMatrix();
    glBegin(GL_QUADS);
    
    glColor4f(color.r,color.g,color.b,color.a);
    glNormal3f(normal.x,normal.y,normal.z);
    glVertex3f(corner[0].x,corner[0].y,corner[0].z);
    glVertex3f(corner[1].x,corner[1].y,corner[1].z);
    glVertex3f(corner[2].x,corner[2].y,corner[2].z);
    glVertex3f(corner[3].x,corner[3].y,corner[3].z);
    
    glEnd();
    glPopMatrix();
}

void Plate::update(SDL_Event event){
    
}
