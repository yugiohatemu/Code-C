//
//  camera.cpp
//  Code-C
//
//  Created by Yue on 11/30/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "camera.h"
#include "SDL/SDL_opengl.h"

Camera::Camera(){
    
}

Camera::Camera(Camera const&){
    
}

Camera& Camera::operator=(Camera const&){
    return *this;
}

Camera& Camera::Instance(){
    static Camera m_Instance;
    return m_Instance;
}

//////////////////////////////////////////////////////////////////////

void Camera::init_camera(){
    Vector pos(0,5,8);
    //TODO:pos rotate 90, 
    views[FRONT_VIEW] = pos;
    views[RIGHT_VIEW].set(5, 8, 0);
    views[BACK_VIEW].set(0, 5, -8);
    views[LEFT_VIEW].set(-5, 8, 0);
}

void Camera::switch_view(Point p){
    current_view += 1;
    if (current_view == TOTAL_VIEW) current_view = FRONT_VIEW;
    
    Point new_pos = p + views[current_view];
//    Vector dir = new_pos - p;
//    dir.normalize();
//    std::cout<<dir;
    glLoadIdentity();
    gluLookAt(new_pos.x, new_pos.y, new_pos.z, p.x, p.y, p.z, 0,1,0);
}

Vector Camera::get_direction(SDLKey dir){

    Vector vec;
    switch (dir) {
        case SDLK_LEFT: vec.set(-1, 0, 0); break;
        case SDLK_RIGHT: vec.set(1, 0, 0); break;
        case SDLK_UP: vec.set(0, 0, -1); break;
        case SDLK_DOWN: vec.set(0, 0, 1);break;
        default: break;
    }
    
    //gimbal lock?
    if (current_view == RIGHT_VIEW) vec.rotate('y', -90);
    else if (current_view == BACK_VIEW) vec.rotate('y', 180);
    else if (current_view == LEFT_VIEW) vec.rotate('y', 90);
    
    return vec;
}

