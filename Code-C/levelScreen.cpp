//
//  levelScreenController.cpp
//  Code-C
//
//  Created by Yue on 12/24/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "levelScreen.h"
#include "camera.h"
#include "protagonist.h"
//can be replaced by pathmaker later
#include "pathMaker.h"
#include "utility.h"
#include "screenController.h"
#include <sstream>

LevelScreen::LevelScreen(int selected_level):Screen(){
    Camera::Instance().init_camera();
    Camera::Instance().anime = false;
    
    pro = new Protagonist();
    
    std::stringstream ss; ss<<"level"<<selected_level<<".txt";
    
    std::string full_name = get_absolute_path(ss.str());
    path = PathMaker::make_path_from_file(full_name,this);
//    debug(full_name);
    
    if (path) {
        path->is_ball_on = true;
        pro->current = path;
    }
    
    //set global state now
    ColorRule::Instance().set_global_state(ColorRule::RED);
    //Set it to at the start of path
}

LevelScreen::~LevelScreen(){
    if (pro) delete pro;
    if (path) Path::delete_path(path);
}

//////////////////////////////////////////////////

void draw_orbit(){
    //Draw the x, y, z
    glPushMatrix();
    glBegin(GL_LINES);
    glColor3f(1, 0, 0);glVertex3f(0, 0, 0); glVertex3f(1, 0, 0);
    glColor3f(0, 1, 0);glVertex3f(0, 0, 0); glVertex3f(0, 1, 0);
    glColor3f(0, 0, 1);glVertex3f(0, 0, 0); glVertex3f(0, 0, 1);
    glEnd();
    glPopMatrix();
}

void LevelScreen::win(){
    ScreenController * root_controller = dynamic_cast<ScreenController *>(root);
    root_controller->pop_controller();
    Camera::Instance().init_camera();
}

//Sprite interface
void LevelScreen::render(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor( 1.f, 1.f, 1.f, 1.f );
    Camera::Instance().set_camera();
    draw_orbit();
    if (pro) pro->render();
    if (path) path->render();
}

void LevelScreen::update(SDL_Event event){
    if (event.type == SDL_KEYDOWN) {
        if(event.key.keysym.sym == SDLK_TAB) Camera::Instance().switch_view();
    }
    
    if (pro) pro->update(event);
    if (path) path->update(event);
}