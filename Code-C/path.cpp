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
Path::Path(Point start, Point end, Vector n):start(start), end(end), normal(n){
    to_next = end - start;
    to_next.normalize();
    to_prev = to_next * -1;
    prev = next = NULL;
    normal.normalize();
    //surface
    surface = to_next.cross(normal);
    surface.normalize();
    //test for waht?
//    matrix= basis_matrix(surface, normal, to_next, Point());
    
//    for (int i = 0; i < 4; i += 1) {
//        for (int j = 0; j < 4; j += 1) {
//            std::cout<<matrix[4*j + i]<<" ";
//        }
//        std::cout<<std::endl;
//    }
}


Path::Path(Point start, Point end, Vector nor, Vector sur):start(start), end(end), normal(nor), surface(sur){
    to_next = end - start;
    to_next.normalize();
    to_prev = to_next * -1;
    prev = next = NULL;
    normal.normalize();
    surface.normalize();
    //this one should be correct
//    matrix= basis_matrix(surface, normal, to_next, Point());
//    debug(surface); debug(normal), debug(to_next);
//    for (int i = 0; i < 4; i += 1) {
//        for (int j = 0; j < 4; j += 1) {
//            std::cout<<matrix[4*j + i]<<" ";
//        }
//        std::cout<<std::endl;
//    }
}

void Path::mult_matrix(){
//    glRotatef(angle.x, normal.x, normal.y, normal.z);
//    glMultMatrixf(matrix);
    //shouldnt need to do this translation be this one
//    glTranslatef(start.x, start.y, start.z);
//    glRotatef(angle.y, 0, 1, 0);
//    glRotatef(angle.x, to_next.x, to_next.y, to_next.z);
}

Path::~Path(){
    prev = next = NULL;
}

void Path::render(){
    glPushMatrix();
    
    glBegin(GL_LINES);
    glColor3f(1, 1, 1);
    glVertex3f(start.x, start.y, start.z);
    glVertex3f(end.x, end.y, end.z);
    glEnd();
    
    glTranslatef(start.x, start.y, start.z);
//    glRotatef(angle.x, to_next.x, to_next.y, to_next.z);
    glTranslatef(-start.x, -start.y, -start.z);

    //add rotation here
    glBegin(GL_QUADS);
    glColor3f(1, 0, 0);
    glNormal3f(normal.x, normal.y, normal.z);
    
    glVertex3f(start.x - 0.5 , start.y, start.z);
    glVertex3f(start.x + 0.5 , start.y, start.z);
    glVertex3f(end.x + 0.5, end.y, end.z);
    glVertex3f(end.x - 0.5, end.y, end.z);
    //if we get angels, then we dont need to calculate that again
    glEnd();
    
    glPopMatrix();
}

void Path::update(SDL_Event event){
    
}

Point Path::get_end(){
    return end;
}
Point Path::get_start(){
    return start;
}

Point Path::get_angle(){
    return angle;
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

Path* create_path(std::vector<Point> point_list, std::vector<Vector> normal_list){
    //invalid path
    if (point_list.size() < 2 || point_list.size() - 1 != normal_list.size()) return NULL;
    
    Path * head = new Path(point_list[0],point_list[1], normal_list[0]);
    Path * prev = head;
    for (int i = 1; i < point_list.size()-1; i+= 1) {
        Path * t = new Path(point_list[i], point_list[i+1],normal_list[i]);
        t->prev = prev;
        prev->next = t;
        prev = t;
    }
    
    return head;
}


Path* create_path(std::vector<Point> point_list, std::vector<Vector> normal_list, std::vector<Point> angle_list){
    if (point_list.size() < 2 || point_list.size() - 1 != normal_list.size()) return NULL;
    
    Path * head = new Path(point_list[0],point_list[1], normal_list[0]);
    head->angle = angle_list[0];
    
    Path * prev = head;
    for (int i = 1; i < point_list.size()-1; i+= 1) {
        Path * t = new Path(point_list[i], point_list[i+1],normal_list[i]);
        t->angle = angle_list[i];
        
        t->prev = prev;
        prev->next = t;
        prev = t;
    }
    
    return head;
}

Path* create_path(std::vector<Point> point_list, std::vector<Vector> normal_list, std::vector<Vector> surface_list){
    if (point_list.size() < 2 || point_list.size() - 1 != normal_list.size()) return NULL;
    
    Path * head = new Path(point_list[0],point_list[1], normal_list[0],surface_list[0]);
   
    
    Path * prev = head;
    for (int i = 1; i < point_list.size()-1; i+= 1) {
        Path * t = new Path(point_list[i], point_list[i+1],normal_list[i],surface_list[i]);
        
        t->prev = prev;
        prev->next = t;
        prev = t;
    }
    
    return head;
}

void delete_path(Path * p){
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
void render_path(Path * p){
    
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


