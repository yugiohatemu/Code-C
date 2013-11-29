//
//  track.cpp
//  Code-C
//
//  Created by Yue on 11/28/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "track.h"
#include "SDL/SDL_opengl.h"

Track::Track(){
    
}

Track::~Track(){
    
}

void Track::render(){
    glPushMatrix();
    for (Plate & p : platelist) {
        p.render();
    }
    glPopMatrix();
    
    glPushMatrix();
    
    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 0); glNormal3f(0.0,1.0,0.0);
    glVertex3f(0.0, 0.0,0.0); glVertex3f(0.0, 0.0,1.0);
    glVertex3f(2.0, 0.0,1.0); glVertex3f(2.0, 0.0,0.0);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1.0, 0, 0);glNormal3f(1, 1, 0);
    glVertex3f(2.0, 0.0,1.0);glVertex3f(2.0, 0.0,0.0);
    glVertex3f(3.0, 1.0,0.0);glVertex3f(3.0, 1.0,1.0);
    glEnd();
    
    glBegin(GL_QUADS);
    glColor3f(1.0, 0, 0);glNormal3f(1, -1, 0);
    glVertex3f(3.0, 1.0,0.0);glVertex3f(3.0, 1.0,1.0);
    glVertex3f(2.0, 2.0,1.0);glVertex3f(2.0, 2.0,0.0);
    glEnd();
    
    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 0);glNormal3f(0.0,-1.0,0.0);
    glVertex3f(0.0, 2.0,0.0);glVertex3f(0.0, 2.0,1.0);
    glVertex3f(2.0, 2.0,1.0);glVertex3f(2.0, 2.0,0.0);
    glEnd();
    
    glPopMatrix();

}

void Track::update(SDL_Event event){
    
}