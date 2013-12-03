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

void Protagonist::render(){
    glPushMatrix();
    
    glTranslatef(anchor.x, anchor.y, anchor.z);
    //added
    Path * current = dynamic_cast<Path *>(path);
    Point angle = current->get_angle();
    Vector vec = current->get_to_next();
    glRotatef(angle.y, 0, 1, 0);
    glRotatef(angle.z, vec.x, 0, vec.z);

//    glRotatef(45, 0, 1, 0);
    glColor3f(0, 0, 1.0);
    glutSolidTeapot(0.5);
    
    glPopMatrix();
}

void Protagonist::update(SDL_Event event){
    float speed = 0.1f;
    //cos(angle)=dot(a,b)/(length(a)length(b))
    //so calculate based on each 3 axis
    if (event.type == SDL_KEYDOWN) {
        if(event.key.keysym.sym == SDLK_UP){
            Path * current = dynamic_cast<Path *>(path);
            Point next_anchor = anchor + current->get_to_next() * speed;
        
            if (next_anchor.is_whithin(current->get_start(), current->get_end())) { //if within
                anchor = next_anchor;
            }else{
                anchor = current->get_end();
                if (current->next) path = current->next;
            }
        }else if(event.key.keysym.sym == SDLK_DOWN){
            Path * current = dynamic_cast<Path *>(path);
            Point prev_anchor = anchor + current->get_to_prev() * speed;
            
            if (prev_anchor.is_whithin(current->get_start(), current->get_end())) { //if within
                anchor = prev_anchor;
            }else{
                anchor = current->get_start();
                if (current->prev) path = current->prev;
            }
        }
    }
}

Point Protagonist::get_anchor(){
    return anchor;
}