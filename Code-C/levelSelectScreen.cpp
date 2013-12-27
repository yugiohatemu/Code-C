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
    //TODO: ask for another top down view use different up vector?
    total_level = 5;
    selected_level = 0;
    
    levels = new bool [total_level];
    std::fill(levels, levels + total_level, false);
    levels[selected_level] = true;
    
    Camera::Instance().eye_to_center = Vector(-5,5,0);
    
}

LevelSelectScreen::~LevelSelectScreen(){
    delete [] levels;
}

void LevelSelectScreen::render(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor( 1.f, 1.f, 1.f, 1.f );
    //Use orthogonoal view?
    Camera::Instance().set_camera();
    Camera::Instance().center = Point(0,0,selected_level);
    
    for (int i = 0; i < total_level; i++) {
        if (levels[i]) glColor3f(1, 0, 0);
        else glColor3f(1, 1, 1);
        
        glPushMatrix();
        glTranslatef(0, 0, i);
        glBegin(GL_QUADS);
        glVertex3f(0, 0, 0); glVertex3f(1, 0, 0);
        glVertex3f(1, 0, 1); glVertex3f(0, 0, 1);
        glEnd();
        glPopMatrix();
    }
    
    //To be honest I really want a level* sprite!!!
}

void LevelSelectScreen::update(SDL_Event event){
    if (event.type == SDL_KEYDOWN) {
        if(event.key.keysym.sym == SDLK_RETURN){
            ScreenController * root_controller = dynamic_cast<ScreenController *>(root);
            root_controller->push_controller(new LevelScreen(selected_level % 2));
        }else if(event.key.keysym.sym == SDLK_RIGHT){
            levels[selected_level] = false;
            selected_level += 1; if(selected_level == total_level) selected_level = 0;
            levels[selected_level] = true;
        }else if(event.key.keysym.sym == SDLK_LEFT){
            levels[selected_level] = false;
            selected_level -= 1; if(selected_level < 0) selected_level = total_level-1;
            levels[selected_level] = true;
        }
    }

}