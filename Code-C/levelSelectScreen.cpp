//
//  levelSelectScreen.cpp
//  Code-C
//
//  Created by Yue on 12/24/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "levelSelectScreen.h"
#include "camera.h"
#include "levelScreen.h"
#include "screenController.h"
#include "SDL/SDL_opengl.h"
#include <GLUT/GLUT.h>

LevelSelectScreen::LevelSelectScreen():Screen(){
    Camera::Instance().init_camera();
}

LevelSelectScreen::~LevelSelectScreen(){
    
}

void LevelSelectScreen::render(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor( 1.f, 1.f, 1.f, 1.f );
    //I suggest the level Screen ask it to reset
    Camera::Instance().set_camera();
    glPushMatrix();
    glColor3f(1, 0, 0);
    glutSolidTeapot(1);
    glPopMatrix();
    //just ask for a reset, easy
}

void LevelSelectScreen::update(SDL_Event event){
    if (event.type == SDL_KEYDOWN) {
        if(event.key.keysym.sym == SDLK_RETURN){
            ScreenController * root_controller = dynamic_cast<ScreenController *>(root);
            root_controller->push_controller(new LevelScreen());
        }
    }

}