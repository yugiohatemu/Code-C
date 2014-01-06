//
//  levelSprite.cpp
//  Code-C
//
//  Created by Yue on 12/27/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "levelSprite.h"
#include "SDL/SDL_opengl.h"
#include "shape.h"

LevelSprite::LevelSprite(){
    selected = false;
    orien = 0;
    shape = new Shape();
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
    glRotatef(orien, 0, 0, 1);
    shape->render();
    glPopMatrix();
}

void LevelSprite::update(SDL_Event event){
    if (selected) {
        orien += 5; if(orien >= 180) orien = 0;
    }
}