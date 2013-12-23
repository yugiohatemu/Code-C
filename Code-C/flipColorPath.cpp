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

FlipColorPath::FlipColorPath(Vector trans, std::vector<Vector> rotate_list, std::vector<ColorRule::State> color_list):Path(){
    state = IDLE;
    prod = Matrix::translate(trans);
    
    next_color_state = color_list;
    next_rotate = rotate_list;
    
    cur_rotate = next_rotate[cur_index];
    color_state = next_color_state[cur_index];
}

FlipColorPath::~FlipColorPath(){
    
}

//////////////////////////////////////////////////////////////////////////////////////////
//Overwrite parent class
Vector FlipColorPath::get_normal(){
    Vector norm =prod * Matrix::rotateXYZ(cur_rotate)* Vector(0,1,0);
    norm.normalize();
    return norm;
}

Matrix FlipColorPath::get_transform(){
    return prod * Matrix::rotateXYZ(cur_rotate);
}

bool FlipColorPath::is_on_surface(Point p){
    return Path::is_on_surface(p);
}


/////////////////////////////////////////////////////////////////////////////////////////
//Sprite interface
void FlipColorPath::render(){
    //Draw a triangle to differentiate
    glPushMatrix();
    Matrix final_prod = prod * Matrix::rotateXYZ(cur_rotate);
    glMultMatrixf(final_prod.begin());
    
    if (color_state == ColorRule::RED)glColor4f(1,0,0,1);
    else glColor4f(0, 0, 1, 1); //color blue?
    
    //use two color for that
    glBegin(GL_TRIANGLES);
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
        
        Vector rot = next_rotate[cur_index];
        cur_rotate.x = adjust(cur_rotate.x, rot.x, 3);
        cur_rotate.y = adjust(cur_rotate.y, rot.y, 3);
        cur_rotate.z = adjust(cur_rotate.z, rot.z, 3);
        
    }else if (!is_ball_on) {
        state = IDLE;
        cur_index += 1; if(cur_index == next_rotate.size()) cur_index = 0;
        
        cur_rotate = next_rotate[cur_index];
        color_state = next_color_state[cur_index];
       
    }
    
    next->update(event);
}

