//
//  flipColorPath.cpp
//  Code-C
//
//  Created by Yue on 12/22/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "flipColorPath.h"
#include "utility.h"
#include "SDL/SDL_opengl.h"

FlipColorPath::FlipColorPath(Point trans, Vector rotate, std::vector<ColorRule::State> next_color, std::vector<float> next_orien):
Path(), next_color(next_color), next_orien(next_orien){
    state = IDLE;
    prod = Matrix::translate(trans) * Matrix::rotateXYZ(rotate);
    
    axis = Vector(1, 0 ,0);
    
    cur_index = 0;
    next_index = 1;
    cur_orien = next_orien[0];
    color_state = next_color[0];
    c = ColorRule::Instance().get_color(color_state);
}

FlipColorPath::~FlipColorPath(){
    
}

//////////////////////////////////////////////////////////////////////////////////////////
//Overwrite parent class
Vector FlipColorPath::get_normal(){
    Vector norm =prod * Matrix::rotate(axis, cur_orien)* Vector(0,1,0);
    norm.normalize();
    return norm;
}

//theoretically we can just use
Matrix FlipColorPath::get_transform(){
    return prod * Matrix::rotate(axis, cur_orien);
}

Path::PathType FlipColorPath::get_path_type(){
    return "FlipColorPath";
}


/////////////////////////////////////////////////////////////////////////////////////////
//Sprite interface
void FlipColorPath::render(){
    //Draw a triangle to differentiate
    glPushMatrix();
    
    glMultMatrixf(get_transform().begin());
    glColor4f(c.r, c.g, c.b ,c.a);
    //use two color for that
//    glBegin(GL_TRIANGLES);
//    glNormal3f(0, 1, 0);
//    glVertex3f(0, 0, -0.5); glVertex3f(0, 0, 0.5); glVertex3f(1, 0, 0);
//    glEnd();
    glCallList(2);
    glPopMatrix();
    
    if (next) next->render();
}

void FlipColorPath::update(SDL_Event event){
    //can we ask the event to be blocked?
    if (state ==  IDLE && is_ball_on) {
        state = ANIME;
        //TODO:Add SDL_block event to perform animation
        
    }else if(state == ANIME && is_ball_on){
        
        cur_orien = adjust(cur_orien, next_orien[next_index], 5);
        if(cur_orien == next_orien[next_index]){
            //transit to next state
            cur_index = next_index;
            
            state = ANIME_DONE;
            color_state = next_color[cur_index];
            c = ColorRule::Instance().get_color(color_state);
            
            ColorRule::Instance().set_global_state(color_state);
            next_index += 1; if(next_index == next_color.size()) next_index = 0;
        }
        
    }else if (!is_ball_on && state == ANIME_DONE) {
        state = IDLE;
    }
    
    if (next) next->update(event);
}

