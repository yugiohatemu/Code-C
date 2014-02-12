//
//  spritePath.cpp
//  Code-C
//
//  Created by Yue on 1/14/14.
//  Copyright (c) 2014 Yue. All rights reserved.
//

#include "spritePath.h"
#include "SDL/SDL_opengl.h"
#include "heart.h"

SpritePath::SpritePath(Point trans, Vector rotate):Path(){
    prod = Matrix::translate(trans) * Matrix::rotateXYZ(rotate);
    
    normal = prod * Vector(0,1,0);
    normal.normalize();
    
    sprite = new Heart();
}

SpritePath::~SpritePath(){
    if(sprite)  delete sprite;
}

/////////////////////////////////////////////////////////////////////////////////////////
//Parent overwrite
Vector SpritePath::get_normal(){
    return normal;
}

Matrix SpritePath::get_transform(){
    return prod;
}

Path::PathType SpritePath::get_path_type(){
    return "SpritePath";
}

/////////////////////////////////////////////////////////////////////////////////////////
//Sprite interface
void SpritePath::render(){
    glPushMatrix();
    glColor4f(c.r, c.g, c.b, c.a);
    glMultMatrixf(prod.begin());
    glCallList(3);
    glTranslatef(0, 0.5, 0);
    if(sprite)  sprite->render();
    glPopMatrix();
    
    if(next) next->render();
}

void SpritePath::update(SDL_Event event){
    if(next) next->update(event);
}
///////////////////////////////////////////////////////////////////////////////////////

Sprite* SpritePath::give_sprite(){
    Sprite * s = sprite;
    sprite = NULL;
    return s;
}

void SpritePath::set_sprite(Sprite * s){
    sprite = s;
}