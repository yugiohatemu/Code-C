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
            anchor = anchor + Vector(1,0,0) * speed;
            //we can use the accurate matrix to do the calculation for anchor
            //and then use start and end to test if we need to go next
            
//            Path * current = dynamic_cast<Path *>(path);
//            Point next_anchor = anchor + current->get_to_next() * speed;
        
//            if (next_anchor.is_whithin(current->get_start(), current->get_end())) { //if within
//                anchor = next_anchor;
//            }else{
//                anchor = current->get_end();
//                if (current->next) path = current->next;
//            }
        }else if(event.key.keysym.sym == SDLK_DOWN){
            anchor = anchor + Vector(1,0,0) * -speed;
//            Path * current = dynamic_cast<Path *>(path);
//            Point prev_anchor = anchor + current->get_to_prev() * speed;
            
//            if (prev_anchor.is_whithin(current->get_start(), current->get_end())) { //if within
//                anchor = prev_anchor;
//            }else{
//                anchor = current->get_start();
//                if (current->prev) path = current->prev;
//            }
        }
    }
}

Point Protagonist::get_anchor(){
    return anchor;
}