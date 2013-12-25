//
//  endPath.cpp
//  Code-C
//
//  Created by Yue on 12/23/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "endPath.h"
#include "SDL/SDL_opengl.h"
#include "levelScreen.h"

EndPath::EndPath(Vector trans, Vector rotate):Path(){
    prod = Matrix::translate(trans) * Matrix::rotateXYZ(rotate);
    color_state = ColorRule::BLACK;
    
    normal = prod * Vector(0,1,0);
    normal.normalize();

}

EndPath::~EndPath(){
    
}

//////////////////////////////////////////////////////////////////////////////////////////
//Overwrite parent class
Vector EndPath::get_normal(){
    return normal;
}

Matrix EndPath::get_transform(){
    return prod;
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
    
    if (next) next->render();
}

void EndPath::update(SDL_Event event){
    if (is_ball_on) {
        screen->win();
    }
    //we don't have a next, haha
    if (next) next->update(event);
}
