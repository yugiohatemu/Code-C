//
//  dyePath.cpp
//  Code-C
//
//  Created by Yue on 1/9/14.
//  Copyright (c) 2014 Yue. All rights reserved.
//

#include "dyePath.h"
#include "dye.h"
#include "SDL/SDL_opengl.h"

DyePath::DyePath(Point trans, Vector rotate, ColorRule::State dye_color):Path(){
    prod = Matrix::translate(trans) * Matrix::rotateXYZ(rotate);
    normal = prod * Vector(0,1,0);
    normal.normalize();
    //depends on color state
    dye = new Dye(dye_color);
}

DyePath::~DyePath(){
    delete dye;
}

/////////////////////////////////////////////////////////////////////////////////////////

Dye* DyePath::get_dye(){
    //give a copy of the current dye?
    return dye->copy();
}


//////////////////////////////////////////////////////////////////////////////////////////
//Overwrite parent class
Vector DyePath::get_normal(){
    return normal;
}

Matrix DyePath::get_transform(){
    return prod;
}

Path::PathType DyePath::get_path_type(){
    return "DyePath";
}

/////////////////////////////////////////////////////////////////////////////////////////
//Sprite interface
void DyePath::render(){
    glPushMatrix();
    glColor4f(c.r, c.g, c.b, c.a);
    glMultMatrixf(prod.begin());
    glCallList(3);
    dye->render();
    glPopMatrix();
    next->render();
}

void DyePath::update(SDL_Event event){
    //already has a dye, give a clone/copy to protagonist?
    next->update(event);
}