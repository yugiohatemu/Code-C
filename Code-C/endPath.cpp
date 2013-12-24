//
//  endPath.cpp
//  Code-C
//
//  Created by Yue on 12/23/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "endPath.h"
#include "SDL/SDL_opengl.h"

EndPath::EndPath(Vector trans, Vector rotate):Path(){
    prod = Matrix::translate(trans) * Matrix::rotateXYZ(rotate);
    color_state = ColorRule::BLACK;
}

EndPath::~EndPath(){
    
}

//////////////////////////////////////////////////////////////////////////////////////////
//Overwrite parent class
Vector EndPath::get_normal(){
    return Path::get_normal();
}

Matrix EndPath::get_transform(){
    return Path::get_transform();
}

bool EndPath::is_on_surface(Point p){
    return Path::is_on_surface(p);
}

/////////////////////////////////////////////////////////////////////////////////////////
//Sprite interface

void EndPath::render(){
    glPushMatrix();
    glMultMatrixf(get_transform().begin());
    glBegin(GL_TRIANGLES);
    glColor3f(1, 0, 0); glNormal3f(0, 1, 0);
    glVertex3f(0, 0, -0.5); glVertex3f(0, 0, 0.5); glVertex3f(1, 0, 0.5);
    glColor3f(0, 0, 1); glNormal3f(0, 1, 0);
    glVertex3f(1, 0, -0.5); glVertex3f(1, 0, 0.5); glVertex3f(0, 0, -0.5);
    glEnd();
    glPopMatrix();
}

void EndPath::update(SDL_Event event){
    if (is_ball_on) {
        //call the scene to outstop the current level
        //
    }
    //we don't have a next, haha
}
