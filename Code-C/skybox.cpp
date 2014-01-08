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
#include "shapeBuilder.h"

Skybox::Skybox(){
    //I suggest make it simple for now, but distinctive from other things.
    //(0, h,-5) (0 ,h ,5) (5, h, -5) (5, h,5)
    
}

Skybox::~Skybox(){
    
}

//////////////////////////////////////////////////////////////////////////////////////
//Sprite interface

void Skybox::render(){
    glPushMatrix();
    glColor3f(0, 0, 0);
    glTranslatef(center.x, center.y, center.z);
    //this applies to the whole scene?, or not?
    //because for now it appears that we are just adding random things to scene, but not he sky box.
    glCallList(2);
    glPopMatrix();
    
}
void Skybox::update(SDL_Event event){
    center = Camera::Instance().center;
}
