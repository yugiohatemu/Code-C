//
//  levelSprite.cpp
//  Code-C
//
//  Created by Yue on 12/27/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "levelSprite.h"
#include "SDL/SDL_opengl.h"

LevelSprite::LevelSprite(){
    selected = false;
    orien = 0;
}

LevelSprite::~LevelSprite(){
    
}

void LevelSprite::set_selected(bool s){
    selected = s;
}

void LevelSprite::render(){
    if (selected) glColor3f(1, 0, 0);
    else glColor3f(0, 0, 0);
    
    glPushMatrix();
    glRotatef(orien, 1, 0, 0);
    glBegin(GL_QUADS);
    glNormal3f(0, 1, 0);
    glVertex3f(0, 0, -0.5); glVertex3f(0, 0, 0.5); glVertex3f(1, 0, 0.5); glVertex3f(1, 0, -0.5);
    glEnd();
    glPopMatrix();
}

void LevelSprite::update(SDL_Event event){
    if (selected) {
        orien += 5; if(orien >= 180) orien = 0;
    }
}