//
//  flipColorPath.cpp
//  Code-C
//
//  Created by Yue on 12/22/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "flipColorPath.h"
#include "colorRule.h"
#include "utility.h"
#include "SDL/SDL_opengl.h"

FlipColorPath::FlipColorPath(Vector trans, Vector rotate):Path(){
    state = IDLE;
    prod = Matrix::translate(trans) * Matrix::rotateXYZ(rotate);
    
    axis = Vector(1, 0 ,0);
    orien = 0;
}

FlipColorPath::~FlipColorPath(){
    
}

//////////////////////////////////////////////////////////////////////////////////////////
//Overwrite parent class
Vector FlipColorPath::get_normal(){
    Vector norm =prod * Matrix::rotate(axis, orien)* Vector(0,1,0);
    norm.normalize();
    return norm;
}

//theoretically we can just use
Matrix FlipColorPath::get_transform(){
    return prod * Matrix::rotate(axis, orien);
}

bool FlipColorPath::is_on_surface(Point p){
    return Path::is_on_surface(p);
}


/////////////////////////////////////////////////////////////////////////////////////////
//Sprite interface
void FlipColorPath::render(){
    //Draw a triangle to differentiate
    glPushMatrix();
    
    glMultMatrixf(get_transform().begin());
    if (color_state == ColorRule::RED)glColor4f(1,0,0,1);
    else glColor4f(0, 0, 1, 1); //color blue?
    
    //use two color for that
    glBegin(GL_TRIANGLES);
    glNormal3f(0, 1, 0);
    glVertex3f(0, 0, -0.5); glVertex3f(0, 0, 0.5); glVertex3f(1, 0, 0);
    glEnd();
    glPopMatrix();
    
    next->render();
}

void FlipColorPath::update(SDL_Event event){
    //can we ask the event to be blocked?
    if (state ==  IDLE && is_ball_on) {
        state = ANIME;
        //TODO:Add SDL_block event to perform animation
        
    }else if(state == ANIME && is_ball_on){
        if (color_state == ColorRule::BLUE ) {
            orien = adjust(orien, 0, 5);
            if (orien == 0) {
                state = ANIME_DONE;
                color_state  = ColorRule::RED;
                ColorRule::Instance().set_global_state(color_state);
            }
        }else if(color_state == ColorRule::RED){
            orien = adjust(orien, 180, 5);
            if (orien == 180) {
                state = ANIME_DONE;
                color_state  = ColorRule::BLUE;
                ColorRule::Instance().set_global_state(color_state);
            }
        }
       
    }else if (!is_ball_on && state == ANIME_DONE) {
        state = IDLE;
    }
    
    next->update(event);
}

