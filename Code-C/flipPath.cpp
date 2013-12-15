//
//  flipPath.cpp
//  Code-C
//
//  Created by Yue on 12/14/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "flipPath.h"
#include "stopWatch.h"
#include "SDL/SDL_opengl.h"

FlipPath::FlipPath(Vector trans, std::vector<Vector> next_list):Path(){
    prod = Matrix::translate(trans);
    next_rotate = next_list;
    
    for (int i = 0; i < next_rotate.size(); i++) {
        Matrix final_prod = prod * Matrix::rotateXYZ(next_rotate[i]);
        end_point_list.push_back(final_prod * end);
    }
}

FlipPath::~FlipPath(){
    //delete everything except the cur_prev, if it exists
    //TODO: glitch through
    for (int i = 1; i < next_path.size();i++){
        delete_path(next_path[i]);
    }
}

void FlipPath::add_next_path(Path * p){
    next_path.push_back(p);
    cur_next = next_path[0];
}


std::vector<Point> FlipPath::get_end_point_list(){
    return end_point_list;
}

void FlipPath::anime(){
    /*
     In order for the animation to work, we only need the rotation matrix
     I think this force us to seperate the matrix instead of just using the final product
    
     */
}

//////////////////////////////////////////////////////////////////////////////////////////
//Overwrite parent class

Matrix FlipPath::get_transform(){
    return prod * Matrix::rotateXYZ(next_rotate[0]);
}

Vector FlipPath::get_normal(){
    Vector norm =prod * Matrix::rotateXYZ(next_rotate[0])* Vector(0,1,0);
    norm.normalize();
    return norm;
}

Path* FlipPath::get_prev_path(){
    return prev;
}

Path* FlipPath::get_next_path(){
    return cur_next;
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
    for (int i = 0; i < 1; i++) {
        glPushMatrix();
        Matrix final_prod = prod * Matrix::rotateXYZ(next_rotate[i]);
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
    }
    
    
    for (int i = 0; i < next_path.size();i++) {
        next_path[i]->render();
    }
}


void FlipPath::update(SDL_Event event){
    
}