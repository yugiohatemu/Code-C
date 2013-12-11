//
//  protagonist.cpp
//  Code-C
//
//  Created by Yue on 11/28/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "protagonist.h"
#include "SDL/SDL_opengl.h"
#include <GLUT/GLUT.h>
#include "camera.h"
#include "path.h"
#include "utility.h"


Protagonist::Protagonist(){
    
}

Protagonist::~Protagonist(){
    
}

//TODO: test for null situation to avoid crush
void Protagonist::render(){
    glPushMatrix();
   
    Path * current = dynamic_cast<Path *>(path);
    Matrix m = current->get_transform();
    glMultMatrixf(m.begin());
    glTranslatef(anchor.x, anchor.y, anchor.z);
    
    glColor3f(0, 0, 1.0);
    glutSolidTeapot(0.5);
    
    glPopMatrix();
}

void Protagonist::update(SDL_Event event){
    float speed = 0.1f;
    
    if (event.type == SDL_KEYDOWN) {
        if(event.key.keysym.sym == SDLK_UP){

            Path * current = dynamic_cast<Path *>(path);
            Point next_anchor = current->get_transform() * (anchor + Vector(1,0,0) * speed);
            
            if (next_anchor.is_whithin(current->get_start(), current->get_end())) { //if within
                anchor = anchor+ Vector(1,0,0) * speed;
            }else{
                //reset anchor to avoid over multiply translation
                if (current->next) {
                    path = current->next;
                    anchor = Point(); //current->prev->get_start, before multiplicaton
                }
            }
        }else if(event.key.keysym.sym == SDLK_DOWN){
           
            Path * current = dynamic_cast<Path *>(path);
            Point prev_anchor = current->get_transform() * ( anchor + Vector(1,0,0) * -speed);
            
            if (prev_anchor.is_whithin(current->get_start(), current->get_end())) { //if within
                anchor = anchor + Vector(1,0,0) * -speed;
            }else{
                //reset anchor point
                if (current->prev) {
                    //one way is to get ,or say scale, because invert is inaccurate
                    path= current->prev;
                    anchor = current->prev->get_length_point();
                }
            }
        }
    }
}

Point Protagonist::get_anchor(){
    Path * current = dynamic_cast<Path *>(path);
    Matrix m = current->get_transform();
    return m * anchor;
}

//Simple hack to give normal to camera, might be replaced latter
Vector Protagonist::get_normal(){
    Path * current = dynamic_cast<Path *>(path);
    return current->get_normal();
}