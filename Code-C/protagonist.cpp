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
    glColor3f(0, 0, 1.0);
    glutSolidCube(0.5);
    
    glPopMatrix();
}

void Protagonist::update(SDL_Event event){
    float speed = 0.1f;
    //cos(angle)=dot(a,b)/(length(a)length(b))
    //so calculate based on each 3 axis
    if (event.type == SDL_KEYDOWN) {
        Path * current = dynamic_cast<Path *>(path);
        Point next_anchor = anchor + current->get_to_next() * speed;
        //now, get angel?, vector<1, 0, -1>
        //how do we rotate to that?
        //for each plane, rotate respectively, I guess?
        //so for 1, -1, will be 45 degree around y axis
        if (next_anchor.is_whithin(current->get_start(), current->get_end())) { //if within
            anchor = next_anchor;
        }else{
            anchor = current->get_end();
            if (current->next) path = current->next;
        }
    }
}

Point Protagonist::get_anchor(){
    return anchor;
}