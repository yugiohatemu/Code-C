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
    for (int i = 0; i < next_path.size();i++){
        delete_path(next_path[i]);
    }
}

void FlipPath::add_next_path(Path * p){
    next_path.push_back(p);
}

std::vector<Path *> FlipPath::get_next_path(){
    return next_path;
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
//Vector FlipPath::get_normal(){
//    return normal;
//}
//
//Point FlipPath::get_end(){
//    
//}
//Point FlipPath::get_start(){
//    
//}
//Matrix FlipPath::get_transform(){
//    
//}
//
//Point FlipPath::get_length_point(){
//    
//}
//
//bool FlipPath::is_on_surface(Point p){
//    
//}

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
    for (int i = 0; i < next_rotate.size(); i++) {
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