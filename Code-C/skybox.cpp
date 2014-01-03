//
//  skybox.cpp
//  Code-C
//
//  Created by Yue on 1/2/14.
//  Copyright (c) 2014 Yue. All rights reserved.
//

#include "skybox.h"
#include "camera.h"
#include "SDL/SDL_opengl.h"

Skybox::Skybox(){
    
}

Skybox::~Skybox(){
    
}

//////////////////////////////////////////////////////////////////////////////////////
//Sprite interface

void Skybox::render(){
    //works, so now lets try something new,
    //we can add list of primitives to make things easier
    //before that, we should know that the sky box should be able to warp the level
    //but should also based on the level size
    glPushMatrix();
    glColor3f(0, 0, 0);
    glTranslatef(center.x, center.y, center.z);
    glBegin(GL_TRIANGLES);
    glNormal3f(0, 1, 0);
    glVertex3f(0, 1, 1); glVertex3f(0.5, 1, 0); glVertex3f(-0.5, 1, 0);
    glEnd();
    glPopMatrix();
    
}
void Skybox::update(SDL_Event event){
    center = Camera::Instance().center;
}
