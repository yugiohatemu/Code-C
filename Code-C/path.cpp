//
//  path.cpp
//  Code-C
//
//  Created by Yue on 11/30/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "path.h"
#include "SDL/SDL_opengl.h"
#include "utility.h"

Path::Path(Vector trans, Vector rotate, Vector scale){
    
    prod = Matrix::translate(trans) * Matrix::roatate(Vector(1,0,0), rotate.x)
        * Matrix::roatate(Vector(0,1,0), rotate.y) * Matrix::roatate(Vector(0,0,1), rotate.z);

    //actually, if there is scale here, I want to scale first and seperate the matrix from scalling
    end =  prod * Matrix::scale(scale) * Point(0.5,0,0);
    start = prod * Matrix::scale(scale) * Point(-0.5,0,0);
    normal = prod * Vector(0,1,0);
    
    to_next = end - start;
    to_next.normalize();
    to_prev = -1 * to_next;
    
    prev = next = NULL;
}


Path::~Path(){
    prev = next = NULL;
}

Matrix Path::get_transform(){
    return prod;
}

void Path::render(){
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
}

void Path::update(SDL_Event event){
    
}

Point Path::get_end(){
    return end;
}
Point Path::get_start(){
    return start;
}

Vector Path::get_to_next(){
    return to_next;
}

Vector Path::get_to_prev(){
    return to_prev;
}

Vector Path::get_normal(){
    return normal;
}

////////////////////////////////////////////////////////////////////////////////////////////////



void delete_path(Path * p){
    if (p){
        Path * prev = p->prev;
        Path * next = p;
        
        while (prev != NULL) {
            Path * temp = prev->prev;
            delete prev;
            prev = temp;
        }
        while (next != NULL) {
            Path * temp = next->next;
            delete next;
            next = temp;
        }
    }
}
void render_path(Path * p){
    
    if (p){
        Path * prev = p->prev;
        Path * next = p;
        
        while (prev != NULL) {
            Path * temp = prev->prev;
            prev->render();
            prev = temp;
        }
        while (next != NULL) {
            Path * temp = next->next;
            next->render();
            next = temp;
        }
    }
}


