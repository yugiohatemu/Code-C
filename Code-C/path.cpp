//
//  path.cpp
//  Code-C
//
//  Created by Yue on 11/30/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "path.h"
#include "SDL/SDL_opengl.h"
#include "utility.h"

//    v3----- v2
//   /|      /|
//  v0------v1|
//  | |     | |
//  | |v7---|-|v6
//  |/      |/
//  v4------v5

//v0 0, 0, -0.5
//v1 0, 0, 0.5
//v2 1, 0, 0.5
//v3 1, 0, -0.5
//v4 0, -0.1, -0.5
//v5 0, -0.1, 0.5
//v6 1, -0.1, 0.5
//v7 1, -0.1, -0.5

//Glitch
int indices[24] = {
    0, 1, 2, 3,//top
    4 ,5, 6, 7,//bot
    0, 1, 5, 4,//front
    3, 2, 6, 7,//back
    0, 3, 7, 4,//left
    1, 2, 6, 5//right
};

Path::Path(){
    vertexs[0] = Point(0, 0, -0.5);vertexs[1] = Point(0, 0, 0.5); //we force it to be zero to save translation
    vertexs[2] = Point(1, 0, 0.5);vertexs[3] = Point(1, 0, -0.5);
    for (int i = 4; i < 8; i++) {
        vertexs[i] = vertexs[i-4]; vertexs[i].y = -0.1;
    }
    normals[0] = Vector(0, 1, 0); normals[1] = Vector(0, -1, 0);
    normals[2] = Vector(0, 0, 1); normals[3] = Vector(0, 0, -1);
    normals[4] = Vector(1, 0, 0); normals[5] = Vector(-1, 0, 0);
    
    start = Point::get_mid(vertexs[0], vertexs[1]);
    end = Point::get_mid(vertexs[2], vertexs[3]);
    
    prev = next = NULL;
    
    color_state = ColorRule::RED;
}

Path::Path(Point trans, Vector rotate, Vector scale){
    
    vertexs[0] = Point(0, 0, -0.5);vertexs[1] = Point(0, 0, 0.5); //we force it to be zero to save translation
    vertexs[2] = Point(1, 0, 0.5);vertexs[3] = Point(1, 0, -0.5);
    for (int i = 4; i < 8; i++) {
        vertexs[i] = vertexs[i-4]; vertexs[i].y = -0.1;
    }
    normals[0] = Vector(0, 1, 0); normals[1] = Vector(0, -1, 0);
    normals[2] = Vector(0, 0, 1); normals[3] = Vector(0, 0, -1);
    normals[4] = Vector(1, 0, 0); normals[5] = Vector(-1, 0, 0);
    
    //seperate scale from final matrix
    for (int i = 0; i < 8; i++) vertexs[i] = Matrix::scale(scale) * vertexs[i];
    start = Point::get_mid(vertexs[0], vertexs[1]);
    end = Point::get_mid(vertexs[2], vertexs[3]);
    
    prev = next = NULL;
    prod = Matrix::translate(trans) * Matrix::rotateXYZ(rotate);

    normal = prod * Vector(0,1,0); normal.normalize();

    //for a single , it is right for now
    to_next = end - start;
    to_next.normalize();
    to_prev = -1 * to_next;
    
    color_state = ColorRule::RED;
}


Path::~Path(){
    prev = next = NULL;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
//Getters
Matrix Path::get_transform(){
    return prod;
}


bool Path::is_path_color_valid(){
    return ColorRule::Instance().is_state_global(color_state);
}

Point Path::get_end(){
    return end;
}

Point Path::get_start(){
    return start;
}

Vector Path::get_normal(){
    return normal;
}

Point Path::get_length_point(){
    return Point::get_mid(vertexs[2], vertexs[3]);
}

bool Path::is_on_surface(Point p){ //theoretically we can use the one before product...
    //0 -> 3 is surface
    
    return is_num_whithin(p.x, vertexs[0].x, vertexs[2].x)&&
        is_num_whithin(p.y, vertexs[0].y, vertexs[2].y) &&
        is_num_whithin(p.z, vertexs[0].z, vertexs[2].z);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//Sprite interface
void Path::render(){
    if (is_path_color_valid()) {
        glPushMatrix();
        glColor4f(c.r, c.g, c.b, c.a);
        glMultMatrixf(prod.begin());
//        glBegin(GL_QUADS);
//        
//        for (int i = 0; i < 6; i++) {
//            glNormal3f(normals[i].x, normals[i].y, normals[i].z);
//            for (int j = 0; j < 4; j++) {
//                int index = indices[4*i+j];
//                glVertex3f(vertexs[index].x, vertexs[index].y, vertexs[index].z);
//            }
//        }
//        
//        glEnd();
        glCallList(3);
        glPopMatrix();
    }else{
        glPushMatrix();
        glMultMatrixf(prod.begin());
        glColor3f(0, 0, 0);
        glBegin(GL_LINE_LOOP);
        for (int i = 0;i < 4; i++) glVertex3f(vertexs[i].x, vertexs[i].y, vertexs[i].z);
        glEnd();
        glPopMatrix();
    }
    
    if (next) next->render();
}

void Path::update(SDL_Event event){
    if (next) next->update(event);
}

////////////////////////////////////////////////////////////////////////////////////////////////
//Static methods

void Path::delete_path(Path * root){
    while (root) {
        Path * temp = root->next;
        delete root;
        root = temp;
    }
}

void Path::link_path(Path * p, Path * n){
    p->next = n;
    n->prev = p;
}

void Path::unlink_path(Path * p, Path * n){
    p->next = NULL;
    n->prev = NULL;
}

Path* Path::end_of_path(Path *p){
    if (p) {
        while (p->next)p = p->next;
    }
    return p;
}

