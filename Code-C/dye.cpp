//
//  dye.cpp
//  Code-C
//
//  Created by Yue on 1/9/14.
//  Copyright (c) 2014 Yue. All rights reserved.
//

#include "dye.h"
#include "SDL/SDL_opengl.h"

Dye::Dye(ColorRule::State s){
    c = ColorRule::Instance().get_color(s);
}

Dye::~Dye(){
    
}

//////////////////////////////////////////////////////////////////////////////
Dye* Dye::copy(){
    return new Dye(color_state);
}

//////////////////////////////////////////////////////////////////////////////
//Sprite interface

void Dye::render(){
    //draw a small triangle now?
    glPushMatrix();
    glTranslatef(0, 0.5, 0);
//    if(ColorRule::Instance().is_state_global(color_state)){
        glColor4f(c.a, c.g, c.b,c.a);
        glBegin(GL_TRIANGLES);
        glNormal3f(0, 1, 0);
//    }else{
//        glColor3f(0, 0, 0);
//        glBegin(GL_LINE_LOOP);
//    }
//    
    glVertex3f(0, 0, -0.3); glVertex3f(0, 0, 0.3); glVertex3f(0.3, 0, 0);
    glEnd();
    glPopMatrix();
}
void Dye::update(SDL_Event event){
    //will use whoever that is currently holding the dye
    //the holder will take case of dye's transformation
}