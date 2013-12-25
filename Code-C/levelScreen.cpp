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
#include "path.h"
#include "flipPath.h"
#include "flipColorPath.h"
#include "endPath.h"

#include "utility.h"

#include "screenController.h"

LevelScreen::LevelScreen():Screen(){
    Camera::Instance().init_camera();
    Camera::Instance().anime = false;
    
    pro = new Protagonist();
    std::vector<Vector> trans_list;
    trans_list.push_back(Vector(0,0,0));trans_list.push_back(Vector(1,1,1));
    trans_list.push_back(Vector(0,30,45));trans_list.push_back(Vector(1,1,1));
    
    //need to change the make
    path  = Path::make_consecutive_path(Vector(0,0,0), trans_list, Color(1,0,0));
    
    //go to the end of path
    Path * end_of_path = path;
    while (end_of_path->next) end_of_path = end_of_path->next;
    
    //process flip
    Point end =  end_of_path->get_transform() * end_of_path->get_end();
    //end flip
    EndPath * end_path = new EndPath(Vector(end.x, end.y,end.z), Vector(45,45, 0)); end_path->screen = this;
    Path::link_path(end_of_path,end_path);
    
    //set global state now
    ColorRule::Instance().set_global_state(ColorRule::RED);
    //Set it to at the start of path
    
    pro->current = path;
    path->is_ball_on = true;
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