//
//  flipPath.cpp
//  Code-C
//
//  Created by Yue on 12/14/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "flipPath.h"
#include "SDL/SDL_opengl.h"
#include "utility.h"

FlipPath::FlipPath(Vector trans, std::vector<Vector> next_list):Path(), timer(1){
    prod = Matrix::translate(trans);
    next_rotate = next_list;
    cur_rotate = next_rotate[cur_index];
    state = ANIME;
}

FlipPath::~FlipPath(){
    //Avoid deleteing next multiple time
    for (int i = 0; i < next_path.size();i++) {
        if (next != next_path[i]) {
            delete_path(next_path[i]);
        }
    }
}

void FlipPath::add_next_path(Path * p){
    next_path.push_back(p);
    next = next_path[cur_index];
    next_path[cur_index]->prev = this;
}


std::vector<Point> FlipPath::get_end_point_list(){
    std::vector<Point> list;
    for (int i = 0; i < next_rotate.size(); i++) {
        list.push_back(prod * Matrix::rotateXYZ(next_rotate[i]) * end);
    }
    return list;
}

//////////////////////////////////////////////////////////////////////////////////////////
//Overwrite parent class

Matrix FlipPath::get_transform(){
    return prod * Matrix::rotateXYZ(cur_rotate);
}

Vector FlipPath::get_normal(){
    Vector norm =prod * Matrix::rotateXYZ(cur_rotate)* Vector(0,1,0);
    norm.normalize();
    return norm;
}

bool FlipPath::is_on_surface(Point p){
    
    return Path::is_on_surface(p);
}

/////////////////////////////////////////////////////////////////////////////////////////
//Sprite interface

//TODO: Glitch, remeber to delte and replace with call list or other things later
int ind[24] = {
    0, 1, 2, 3,//top
    4 ,5, 6, 7,//bot
    0, 1, 5, 4,//front
    3, 2, 6, 7,//back
    0, 3, 7, 4,//left
    1, 2, 6, 5//right
};

void FlipPath::render(){
    if (ColorRule::Instance().is_state_global(color_state)) {

        glColor3f(0, 0, 1);
        glPushMatrix();
        Matrix final_prod = prod * Matrix::rotateXYZ(cur_rotate);
        glMultMatrixf(final_prod.begin());
        glBegin(GL_QUADS);
        
        for (int i = 0; i < 6; i++) {
            glNormal3f(normals[i].x, normals[i].y, normals[i].z);
            for (int j = 0; j < 4; j++) {
            int index = ind[4*i+j];
            glVertex3f(vertexs[index].x, vertexs[index].y, vertexs[index].z);
            }
        }
        glEnd();
        glPopMatrix();
    }else{
        glPushMatrix();
        Matrix final_prod = prod * Matrix::rotateXYZ(cur_rotate);
        glMultMatrixf(final_prod.begin());
        glColor3f(0, 0, 0);
        glBegin(GL_LINE_LOOP);
        for (int i = 0;i < 4; i++) glVertex3f(vertexs[i].x, vertexs[i].y, vertexs[i].z);

        glEnd();
        glPopMatrix();
    }
    
    for (int i = 0; i < next_path.size();i++) {
        next_path[i]->render();
    }
    
}



void FlipPath::update(SDL_Event event){
    if (state == STATIC) {
        if (timer.is_timeup()) {
            state = ANIME;
            timer.reset();
        }
    }else{
        //Disconnect path if needed
        if (next) unlink_path(this, next);
        
        //Update index and rotation
        int next_index = cur_index + 1;
        if (next_index >= next_rotate.size()) next_index = 0;
        
        Vector rot = next_rotate[next_index];
        cur_rotate.x = adjust(cur_rotate.x, rot.x, 3);
        cur_rotate.y = adjust(cur_rotate.y, rot.y, 3);
        cur_rotate.z = adjust(cur_rotate.z, rot.z, 3);
        
        if (cur_rotate == rot) {
            cur_index  = next_index;
            link_path(this, next_path[cur_index]);
            
            state = STATIC;
            timer.start();
        }
    }
    
    //Update
    for (int i = 0; i < next_path.size();i++) {
        next_path[i]->update(event);
    }
}