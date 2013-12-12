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
    current = NULL;
}

//TODO: test for null situation to avoid crush
void Protagonist::render(){
    glPushMatrix();
   
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

            Point next_anchor = current->get_transform() * (anchor + Vector(1,0,0) * speed);
            
            if (next_anchor.is_whithin(current->get_start(), current->get_end())) { //if within
                anchor = anchor+ Vector(1,0,0) * speed;
                Camera::Instance().center = next_anchor;
            }else{
                //reset anchor to avoid over multiply translation
                if (current->next) {
                    current = current->next;
                    anchor = Point();
                    
                    Camera::Instance().center = current->get_start();
                    Camera::Instance().up = current->get_normal();
                }
            }
        }else if(event.key.keysym.sym == SDLK_DOWN){
           
            Point prev_anchor = current->get_transform() * ( anchor + Vector(1,0,0) * -speed);
            
            if (prev_anchor.is_whithin(current->get_start(), current->get_end())) { //if within
                anchor = anchor + Vector(1,0,0) * -speed;
                Camera::Instance().center = prev_anchor;
            }else{
                //reset anchor point
                if (current->prev) {
                    //one way is to get ,or say scale, because invert is inaccurate
                    current = current->prev;
                    anchor = current->get_length_point();
                    
                    Camera::Instance().center = current->get_end();
                    Camera::Instance().up = current->get_normal();
                }
            }
        }
    }
}


