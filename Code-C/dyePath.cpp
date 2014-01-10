//
//  dyePath.cpp
//  Code-C
//
//  Created by Yue on 1/9/14.
//  Copyright (c) 2014 Yue. All rights reserved.
//

#include "dyePath.h"

DyePath::DyePath(Point trans, Vector rotate):Path(){
    prod = Matrix::translate(trans) * Matrix::rotateXYZ(rotate);
    
}

DyePath::~DyePath(){
    
}

//////////////////////////////////////////////////////////////////////////////////////////
//Overwrite parent class
Vector DyePath::get_normal(){
    return Path::get_normal();
}

Matrix DyePath::get_transform(){
    return Path::get_transform();
}

/////////////////////////////////////////////////////////////////////////////////////////
//Sprite interface
void DyePath::render(){
    
}

void DyePath::update(SDL_Event event){
    if (event.type == SDL_KEYDOWN) {
        if(event.key.keysym.sym == SDLK_e){
            //create a dye
            //question: how to give it to protagonist
            //we can pass it to level, and level gives it to him
        }
    }
}