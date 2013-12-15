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
    
    for (int i = 0; i < next_rotate.size(); i++) {
        Matrix final_prod = prod * Matrix::rotateXYZ(next_rotate[i]);
        end_point_list.push_back(final_prod * end);
    }
    cur_rotate = next_rotate[cure_indx];
    state = ANIME;
}

FlipPath::~FlipPath(){
    
    for (int i = 0; i < next_path.size();i++){
        //Avoid double delete since the path connected will be handled be delete_path
        if (cure_indx != i) delete_path(next_path[i]);
    }
}

void FlipPath::add_next_path(Path * p){
    next_path.push_back(p);
    cur_next = next_path[cure_indx];
    next_path[cure_indx]->set_prev_path(this);
}


std::vector<Point> FlipPath::get_end_point_list(){
    return end_point_list;
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

Path* FlipPath::get_prev_path(){
    return prev;
}

Path* FlipPath::get_next_path(){
    return cur_next;
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
        if (cur_next) {
            next_path[cure_indx]->set_prev_path(NULL);
            cur_next = NULL;
        }
        
        int next_index = cure_indx + 1;
        if (next_index >= next_rotate.size()) next_index = 0;
        
        Vector rot = next_rotate[next_index];
        cur_rotate.x = adjust(cur_rotate.x, rot.x, 3);
        cur_rotate.y = adjust(cur_rotate.y, rot.y, 3);
        cur_rotate.z = adjust(cur_rotate.z, rot.z, 3);
        
        //TODO: add Camera adjustment
        
        if (cur_rotate == rot) {
            cure_indx  = next_index;
            
            //connect paths together
            cur_next = next_path[cure_indx];
            cur_next->set_prev_path(this);
            
            state = STATIC;
            timer.start();
        }
    }
    
    //Update
    for (int i = 0; i < next_path.size();i++) {
        next_path[i]->update(event);
    }
}