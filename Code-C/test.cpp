//
//  test.cpp
//  Code-C
//
//  Created by Yue on 12/7/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "test.h"
#include "SDL/SDL_opengl.h"
#include "utility.h"

Prim::Prim(){
    angle = 45;
    rotate = Vector(0,1,1);
    translate = Vector(0.5,1,0.5);
    scale = Vector(2,1,1);
    
    Matrix toend = Matrix::roatate(rotate, angle);
    Matrix trans = Matrix::translate(translate);
    Matrix scal = Matrix::scale(scale);
    //so if possible we try to avoid scale?
    //test for mult matri
    
//    Matrix prod = scal * trans * toend;
    prod = toend * trans * scal;
    
    end = Point(0.5,0,0);
    end = prod * end;
    
    //WARNING: when multiply, should be contrary order
    start = Point(-0.5,0,0);
    start = prod * start;
   
    normal = Vector(0,1,0);
    //now we did acurately get the start and end point
}

void Prim::to_test(){
    glRotatef(angle, rotate.x, rotate.y, rotate.z);
    glTranslatef(translate.x, translate.y, translate.z);
//    glScalef(scale.x,scale.y,scale.z);
    
}


void Prim::render(){
    glPushMatrix();
    glBegin(GL_LINES);
    glColor3f(0, 0, 0);
    glVertex3f(start.x, start.y, start.z);
    glVertex3f(end.x, end.y, end.z);
    glEnd();
    glPopMatrix();
    
    //use gldrawarray later
    glPushMatrix();
    glMultMatrixf(prod.begin());

    glColor3f(1, 0, 0);
    
    glBegin(GL_QUADS);
    glNormal3f(normal.x, normal.y, normal.z);
    glVertex3f(-0.5, 0, -0.5);glVertex3f(-0.5, 0, 0.5);
    glVertex3f(0.5, 0, 0.5);glVertex3f(0.5, 0, -0.5);
    glEnd();
    
//    glBegin(GL_LINES);
//    glColor3f(0, 0, 0);
//    glVertex3f(-0.5, 0, 0); //begin for a line
//    glVertex3f(0.5,0,0); //end for a line, so as long as we follow the same translation, we should get the correnct point
//    glEnd();
    
    glPopMatrix();
}

void Prim::update(SDL_Event event){
    
}