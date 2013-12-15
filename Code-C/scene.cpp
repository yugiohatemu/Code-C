//
//  scene.cpp
//  Code-C
//
//  Created by Yue on 12/11/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//
#include "SDL/SDL_opengl.h"
#include "scene.h"
#include "camera.h"
#include "protagonist.h"
#include "path.h"
#include "flipPath.h"
#include "utility.h"
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
    Camera::Instance().anime = false;
    
    pro = new Protagonist();
    std::vector<Vector> trans_list;
    trans_list.push_back(Vector(0,0,0));trans_list.push_back(Vector(2,1,1));
//    trans_list.push_back(Vector(45,0,0));trans_list.push_back(Vector(1,1,1));
//    trans_list.push_back(Vector(0,0,0));trans_list.push_back(Vector(1,1,1));
//    trans_list.push_back(Vector(0,45,0)); trans_list.push_back(Vector(2,1,1));
//    trans_list.push_back(Vector(0,90,0)); trans_list.push_back(Vector(1,1,1));
//    trans_list.push_back(Vector(0,135,0)); trans_list.push_back(Vector(1,1,1));
//    trans_list.push_back(Vector(0,180,0)); trans_list.push_back(Vector(1,1,1));
//    //the orientation does not seperate
//    trans_list.push_back(Vector(45,180,0)); trans_list.push_back(Vector(2,1,1));
//    trans_list.push_back(Vector(60,180,-30)); trans_list.push_back(Vector(1,1,1));
//    trans_list.push_back(Vector(75,180,-60)); trans_list.push_back(Vector(1,1,1));
//    trans_list.push_back(Vector(90,180,-90)); trans_list.push_back(Vector(1,1,1));
    
    //need to change the make
    path  = Path::make_consecutive_path(Vector(.5,0,0), trans_list);
    //TODO: Here need to get to the end of list.....
    Point end =  path->get_transform() * path->get_end();
    
    std::vector<Vector> rotate_list; rotate_list.push_back(Vector(0, 90, 0)); rotate_list.push_back(Vector(0,-90,0));
    //add two paths
    FlipPath * joint = new FlipPath(Vector(end.x, end.y, end.z), rotate_list);
    path->next = joint;
    std::vector<Point> next_end = joint->get_end_point_list();

    for (int i = 0; i < next_end.size(); i++) {
        debug(next_end[i]);
        std::vector<Vector> temp; temp.push_back(Vector(0,0,0)); temp.push_back(Vector(1,1,1));
        Path * child = Path::make_consecutive_path(Vector(next_end[i].x,next_end[i].y,next_end[i].z), temp);
        joint->add_next_path(child);
    }
//
    //////////////
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
//    if (pro) pro->render();
    if (path) Path::render_path(path);
    SDL_GL_SwapBuffers();
}

void Scene::update(SDL_Event event){
    if (event.type == SDL_KEYDOWN) {
        if(event.key.keysym.sym == SDLK_TAB) Camera::Instance().switch_view();
    }

    if (pro) pro->update(event);
}
