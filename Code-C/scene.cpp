//
//  scene.cpp
//  Code-C
//
//  Created by Yue on 12/11/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "scene.h"
#include "camera.h"
#include "path.h"
#include "protagonist.h"
#include "SDL/SDL_opengl.h"

Scene::Scene(){}

Scene::Scene(Scene const &){}

Scene& Scene::operator= (Scene const &){
    return *this;
}

Scene& Scene::Instance(){
    static Scene m_Instance;
    return m_Instance;
}

void Scene::new_scene(){
    Camera::Instance().init_camera();
    
    pro = new Protagonist();
    std::vector<Vector> trans_list;
    trans_list.push_back(Vector(0,0,45));trans_list.push_back(Vector(2,1,1));
    trans_list.push_back(Vector(45,0,0));trans_list.push_back(Vector(1,1,1));
    trans_list.push_back(Vector(0,0,0));trans_list.push_back(Vector(1,1,1));
    path  = Path::make_consecutive_path(Vector(.5,0,0), trans_list);
    pro->current = path;
    
}

void Scene::delete_scene(){
    if (pro) delete pro;
    if (path) Path::delete_path(path);
}

//////////////////////////////////////////////////////////////////////////////////////////
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

void Scene::render(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor( 1.f, 1.f, 1.f, 1.f );
    Camera::Instance().set_camera();
    draw_orbit();
    if (pro) pro->render();
    if (path) Path::render_path(path);
    SDL_GL_SwapBuffers();
}

void Scene::update(SDL_Event event){
    if (pro) pro->update(event);
}