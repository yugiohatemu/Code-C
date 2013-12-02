//
//  plate.cpp
//  Code-C
//
//  Created by Yue on 11/29/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "plate.h"
#include "SDL/SDL_opengl.h"

Plate::Plate(){
    
}

Plate::Plate(Point tl, Point tr, Point bl, Point br, Vector n, Color c):
    top_left(tl), top_right(tr), bot_left(bl), bot_right(br), normal(n), color(c)
{
    
}

Plate::Plate(Point start, Point end, Vector n):start(start), end(end), normal(n){
    color = Color(1,0,0);
}

Plate::~Plate(){
    
}

void Plate::render(){
    glPushMatrix();
    glBegin(GL_QUADS);
    
    glColor4f(color.r,color.g,color.b,color.a);
    
    glNormal3f(normal.x,normal.y,normal.z);
    glVertex3f(top_left.x,top_left.y,top_left.z);
    glVertex3f(top_right.x,top_right.y,top_right.z);
    glVertex3f(bot_right.x,bot_right.y,bot_right.z);
    glVertex3f(bot_left.x,bot_left.y,bot_left.z);
    
    glEnd();
    glPopMatrix();
}

void Plate::update(SDL_Event event){
    
}
