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
//{0, 5 ,10}, {5 ,10, 0}, {0, -5 ,-10}, {5 ,-10, 0}};
void Camera::init_camera(){
    views[FRONT_VIEW].set(0, 5, 10);
    views[RIGHT_VIEW].set(5, 10, 0);
    views[BACK_VIEW].set(0, -5, -10);
    views[LEFT_VIEW].set(5, -10, 0);
}

void Camera::switch_view(){
    
}
