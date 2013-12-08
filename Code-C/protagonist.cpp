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
#include "test.h"

Protagonist::Protagonist(){
    
}

Protagonist::~Protagonist(){
    
}

void Protagonist::render(){
    glPushMatrix();
   
    Prim * current = dynamic_cast<Prim *>(path);
    current->to_test();
    glTranslatef(anchor.x, anchor.y, anchor.z);
    
    glColor3f(0, 0, 1.0);
    glutSolidTeapot(0.5);
    
    glPopMatrix();
}

void Protagonist::update(SDL_Event event){
    float speed = 0.1f;
    //cos(angle)=dot(a,b)/(length(a)length(b))
    //so calculate based on each 3 axis
//    Prim * current = dynamic_cast<Prim *>(path);
//    Vector to_next = current->end - current->start;
    
    if (event.type == SDL_KEYDOWN) {
        if(event.key.keysym.sym == SDLK_UP){
            anchor = anchor + Vector(1,0,0) * 0.1;
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