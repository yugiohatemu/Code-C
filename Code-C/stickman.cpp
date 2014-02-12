//
//  stickman.cpp
//  Code-C
//
//  Created by Yue on 1/16/14.
//  Copyright (c) 2014 Yue. All rights reserved.
//

#include "stickman.h"
#include "SDL/SDL_opengl.h"

Stickman::Stickman(){
    
}

Stickman::~Stickman(){
    
}

void Stickman::render(){
    //translation is controled by path matrix
    glPushMatrix();
    //scale down properly
    //should we do that on ourside? or the blender side?
    
    glPopMatrix();
}

void Stickman::update(SDL_Event event){
    
}