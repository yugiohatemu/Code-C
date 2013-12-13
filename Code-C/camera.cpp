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
    
    up = Vector(1, 0, 0);
    eye = center + Vector(-10,3,0);
}

//do the one without timer now, use timer?
Vector animate_view(Vector cur, Vector next){
    
    float move = 0.1f;
    
    if (next.x >= cur.x){
        if(next.x >= cur.x + move) cur.x += move;
        else cur.x = next.x;
    }else{
        if (next.x <= cur.x - move) cur.x -= move;
        else cur.x = next.x;
    }
    
    if (next.y >= cur.y){
        if(next.y >= cur.y + move) cur.y += move;
        else cur.y = next.y;
    }else{
        if (next.y <= cur.y - move) cur.y -= move;
        else cur.y = next.y;
    }
    
    if (next.z >= cur.z){
        if(next.z >= cur.z + move) cur.z += move;
        else cur.z = next.z;
    }else{
        if (next.z <= cur.z - move) cur.z -= move;
        else cur.z = next.z;
    }
    //there should be a utility function for something like this
    //clamping
    return cur;
    
}

void Camera::anime_camera(Vector next){
    StopWatch timer(0.05);
    
    while (up != next) { //the two vector are not the same, keep calling
        if (timer.is_timeup()) {
            up = animate_view(up, next);
            Scene::Instance().render(); //force the scene to render
            timer.start();
        }
    }
}


void Camera::set_camera(){
    glLoadIdentity();
    eye = center + Vector(-10,3,0);
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

