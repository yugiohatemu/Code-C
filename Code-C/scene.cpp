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
#include "pathMaker.h"
#include "utility.h"

Scene::Scene(){
    new_scene();
}

Scene::~Scene(){
    delete_scene();
}

void Scene::new_scene(){
    Camera::Instance().init_camera();
    Camera::Instance().anime = false;
    
    pro = new Protagonist();
    path  = NULL;
    if (path) {
        path->is_ball_on = true;
        pro->current = path;
    }
   
    //set global state now
    ColorRule::Instance().set_global_state(ColorRule::RED);
    //Set it to at the start of path
    
    
    
    
}

void Scene::win(){
    //so we are direcly asking the level Screen to do that?
    //so scene should be actually be in levelScreen?
    //makes senese
}

//FlipColorPath * flip = new FlipColorPath(Vector(end.x, end.y,end.z), Vector(45,45, 0));
//Path::link_path(end_of_path, flip);
//
////after flip
//Point flip_end = flip->get_transform()* flip->get_end();
//Path * after_flip = Path::make_consecutive_path(Vector(flip_end.x, flip_end.y, flip_end.z), trans_list, Color(0,0,1));
//Path::link_path(flip, after_flip);


//    trans_list.push_back(Vector(0,45,0)); trans_list.push_back(Vector(2,1,1));
//    trans_list.push_back(Vector(0,90,0)); trans_list.push_back(Vector(1,1,1));
//    trans_list.push_back(Vector(0,135,0)); trans_list.push_back(Vector(1,1,1));
//    trans_list.push_back(Vector(0,180,0)); trans_list.push_back(Vector(1,1,1));
//    trans_list.push_back(Vector(45,180,0)); trans_list.push_back(Vector(2,1,1));
//    trans_list.push_back(Vector(60,180,-30)); trans_list.push_back(Vector(1,1,1));
//    trans_list.push_back(Vector(75,180,-60)); trans_list.push_back(Vector(1,1,1));
//    trans_list.push_back(Vector(90,180,-90)); trans_list.push_back(Vector(1,1,1));

//    std::vector<Vector> rotate_list; rotate_list.push_back(Vector(0, 90, 0)); rotate_list.push_back(Vector(0,-90,0));
//    I want rotate around axis, which is basically after the final prod and rotate
//    something wrong about the rotate


//    FlipPath * joint = new FlipPath(Vector(end.x, end.y, end.z), rotate_list);
//    Path::link_path(end_of_path, joint); joint->color_state = ColorRule::BLUE;

//    Keep adding path after joint
//    std::vector<Point> next_end =joint->get_end_point_list();
//    for (int i = 0; i < next_end.size(); i++) {
//        std::vector<Vector> temp;
//        temp.push_back(Vector(0,0,45)); temp.push_back(Vector(1,1,1));
//        temp.push_back(Vector(0,30,45)); temp.push_back(Vector(1,1,1));
//        temp.push_back(Vector(0,60,45)); temp.push_back(Vector(1,1,1));
//        Path * child = Path::make_consecutive_path(Vector(next_end[i].x,next_end[i].y,next_end[i].z), temp, Color(0,0,1));
//        joint->add_next_path(child);
//    }

void Scene::delete_scene(){
    if (pro) delete pro;
    if (path) Path::delete_path(path);
}

//////////////////////////////////////////////////////////////////////////////////////////


void Scene::render(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor( 1.f, 1.f, 1.f, 1.f );
    Camera::Instance().set_camera();
//    draw_orbit();
    if (pro) pro->render();
    if (path) path->render();
    //maybe put in the main?
    
}

void Scene::update(SDL_Event event){
    if (event.type == SDL_KEYDOWN) {
        if(event.key.keysym.sym == SDLK_TAB) Camera::Instance().switch_view();
    }

    if (pro) pro->update(event);
    if (path) path->update(event);
}
