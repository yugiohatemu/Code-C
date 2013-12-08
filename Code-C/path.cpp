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

Path::Path(Vector trans, Vector rotate, Vector scale){
    
    prod = Matrix::translate(trans) * Matrix::roatate(Vector(1,0,0), rotate.x)
        * Matrix::roatate(Vector(0,1,0), rotate.y) * Matrix::roatate(Vector(0,0,1), rotate.z);

    vertexs[0] = Point(-0.5, 0, -0.5);
    vertexs[1] = Point(-0.5, 0, 0.5);
    vertexs[2] = Point(0.5, 0, 0.5);
    vertexs[3] = Point(0.5, 0, -0.5);
    
    for (int i = 0; i < 4; i++)
        vertexs[i] =  Matrix::scale(scale) * vertexs[i];
    
    //actually, if there is scale here, I want to scale first and seperate the matrix from scalling
    end =  prod * Point::get_mid(vertexs[0], vertexs[1]);    //Matrix::scale(scale) * Point(0.5,0,0);
    start = prod * Point::get_mid(vertexs[2], vertexs[3]);
    normal = prod * Vector(0,1,0);
    
    to_next = end - start;
    to_next.normalize();
    to_prev = -1 * to_next;
    
    prev = next = NULL;
}


Path::~Path(){
    prev = next = NULL;
}

Matrix Path::get_transform(){
    return prod;
}

void Path::render(){
    glPushMatrix();
    glBegin(GL_LINES);
    glColor3f(0, 0, 0);
    glVertex3f(start.x, start.y, start.z); glVertex3f(end.x, end.y, end.z);
    glEnd();
    glPopMatrix();
    
    //use gldrawarray later
    glPushMatrix();
    glMultMatrixf(prod.begin());
    glColor3f(1, 0, 0);
    
    glBegin(GL_QUADS);
    glNormal3f(normal.x, normal.y, normal.z);
    for (int i = 0; i < 4; i++)
        glVertex3f(vertexs[i].x, vertexs[i].y, vertexs[i].z);
    
    glEnd();
}

void Path::update(SDL_Event event){
    
}

Point Path::get_end(){
    return end;
}
Point Path::get_start(){
    return start;
}

Vector Path::get_to_next(){
    return to_next;
}

Vector Path::get_to_prev(){
    return to_prev;
}

Vector Path::get_normal(){
    return normal;
}

////////////////////////////////////////////////////////////////////////////////////////////////

void Path::delete_path(Path * p){
    if (p){
        Path * prev = p->prev;
        Path * next = p;
        
        while (prev != NULL) {
            Path * temp = prev->prev;
            delete prev;
            prev = temp;
        }
        while (next != NULL) {
            Path * temp = next->next;
            delete next;
            next = temp;
        }
    }
}
void Path::render_path(Path * p){
    
    if (p){
        Path * prev = p->prev;
        Path * next = p;
        
        while (prev != NULL) {
            Path * temp = prev->prev;
            prev->render();
            prev = temp;
        }
        while (next != NULL) {
            Path * temp = next->next;
            next->render();
            next = temp;
        }
    }
}

Path* Path::make_consecutive_path(Vector start, std::vector<Vector> trans_list){ //in rotate, scale
    ////not enough for a head or not even #
    if (trans_list.size() < 2 || trans_list.size() % 2 != 0) return NULL;
    
    Path * head = new Path(start, trans_list[0], trans_list[1]);
    Path * prev = head;
    
    for (int i = 2; i < trans_list.size(); i += 2) {
        Point p = head->get_end();
        Vector next_start(p.x,p.y,p.z);
        Path * next = new Path(next_start, trans_list[i], trans_list[i+1]);
        
        prev->next = next;
        next->prev = prev;
        prev = next;
        
    }
    
    return head;
}

