//
//  flyPath.cpp
//  Code-C
//
//  Created by Yue on 12/22/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "flyPath.h"
#include "colorRule.h"
#include "SDL/SDL_opengl.h"

FlyPath::FlyPath(Vector start_trans, Vector end_trans):Path(){
    prod = Matrix::translate(start_trans);
    cur_trans = start_trans;
}

FlyPath::~FlyPath(){
    
}

//////////////////////////////////////////////////////////////////////////////////////////
//Overwrite parent class
Vector FlyPath::get_normal(){
    Vector norm = prod * Matrix::translate(cur_trans) * Vector(0,1,0);
    norm.normalize();
    return norm;
}

Matrix FlyPath::get_transform(){
    return prod * Matrix::translate(cur_trans);
}


/////////////////////////////////////////////////////////////////////////////////////////
//Sprite interface
void FlyPath::render(){
    if (ColorRule::Instance().is_state_global(color_state)) {
        
        glPushMatrix();
        Matrix final_prod = prod * Matrix::translate(cur_trans);
        glMultMatrixf(final_prod.begin());
        glColor4f(c.r, c.g, c.b, c.a);
        glBegin(GL_QUADS);
        glNormal3f(0,1,0);
        for (int i = 0; i < 4; i++) glVertex3f(vertexs[i].x, vertexs[i].y, vertexs[i].z);
        glEnd();
        glPopMatrix();
    }else{
        
        glPushMatrix();
        Matrix final_prod = prod * Matrix::translate(cur_trans);
        glMultMatrixf(final_prod.begin());
        glColor3f(0, 0, 0);
        glBegin(GL_LINE_LOOP);
        for (int i = 0;i < 4; i++) glVertex3f(vertexs[i].x, vertexs[i].y, vertexs[i].z);
        glEnd();
        glPopMatrix();
    }
    if (next) next->render();
}

void FlyPath::update(SDL_Event event){
    
    
    if (next) next->update(event);
}