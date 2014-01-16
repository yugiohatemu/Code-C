//
//  text.cpp
//  Code-C
//
//  Created by Yue on 1/14/14.
//  Copyright (c) 2014 Yue. All rights reserved.
//

#include "text.h"
#include "SDL/SDL_opengl.h"
#include <GLUT/GLUT.h>

Text::Text(std::string s):s(s){
    
}

Text::~Text(){
    
}
////////////////////////////////////////
void Text::render(){
    //glLineWidth(2.0);
    //so read a string-> storke it in character
    glPushMatrix();
    glRotatef(-90, 0, 1, 0);
    glScalef(0.008f, 0.008f, 0.008f); //scale it down
    glColor3f(0, 0, 0);
    glutStrokeCharacter(GLUT_STROKE_ROMAN, 'c');
    glPopMatrix();
}

void Text::update(SDL_Event event){
    
}

/* void
 output(GLfloat x, GLfloat y, char *text)
 {
 char *p;
 
 glPushMatrix();
 glTranslatef(x, y, 0);
 for (p = text; *p; p++)
 glutStrokeCharacter(GLUT_STROKE_ROMAN, *p);
 glPopMatrix();
 }*/