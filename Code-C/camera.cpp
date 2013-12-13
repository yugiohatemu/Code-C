//
//  camera.cpp
//  Code-C
//
//  Created by Yue on 11/30/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "SDL/SDL_opengl.h"
#include "SDL/SDL_thread.h"
#include "camera.h"
#include "stopWatch.h"
#include "scene.h"
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
    //now we have matrix, it is much easier to do rotation
    views[FRONT_VIEW] = pos;
    views[RIGHT_VIEW].set(5, 8, 0);
    views[BACK_VIEW].set(0, 5, -8);
    views[LEFT_VIEW].set(-5, 8, 0);
    
    eye_to_center = Vector(-10, 3, 0); //need to applt rotation?
    up = Vector(1, 0, 0);
    eye = center + Vector(-10,3,0);
}


//routine for clamping cur to next using step
float adjust(float cur, float next, float step){
    if (next >= cur){
        if(next >= cur + step) cur += step;
        else cur = next;
    }else{
        if (next <= cur - step) cur -= step;
        else cur = next;
    }
    return cur;
}

void Camera::anime_camera(Vector new_up, Vector new_eye_to_center){
    StopWatch timer(0.05);
    
    while (up != new_up || eye_to_center != new_eye_to_center) { //the two vector are not the same, keep calling
        if (timer.is_timeup()) {
            
            up.x = adjust(up.x, new_up.x, 0.1f);
            up.y = adjust(up.y, new_up.y, 0.1f);
            up.z = adjust(up.z, new_up.z, 0.1f);
            
            //If want to rotation to be more elegant, maybe need to calculate step
            eye_to_center.x = adjust(eye_to_center.x, new_eye_to_center.x, 0.5f);
            eye_to_center.y = adjust(eye_to_center.y, new_eye_to_center.y, 0.5f);
            eye_to_center.z = adjust(eye_to_center.z, new_eye_to_center.z, 0.5f);
            
            Scene::Instance().render(); //force the scene to render
            timer.start();
        }
    }
}

Vector Camera::get_eye_to_center(){
    return Vector(-10,3,0);
}

void Camera::set_camera(){
    glLoadIdentity();
    eye = center + eye_to_center;
    gluLookAt(eye.x, eye.y, eye.z, center.x, center.y, center.z, up.x, up.y, up.z);
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

