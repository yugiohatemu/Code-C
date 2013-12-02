//
//  path.cpp
//  Code-C
//
//  Created by Yue on 11/30/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "path.h"
#include "SDL/SDL_opengl.h"

Path::Path(Point start, Point end, Vector normal):start(start), end(end), normal(normal){
    to_next = start - end;
    to_next.normalize();
    to_prev = to_next * -1;
    prev = next = NULL;
    //surface
    surface = to_next.cross(normal);
    surface.normalize();
}

Path::~Path(){
    prev = next = NULL;
}

void Path::render(){
    glPushMatrix();
    
    glBegin(GL_LINES);
    glColor3f(1, 0, 0);
    glVertex3f(start.x, start.y, start.z);
    glVertex3f(end.x, end.y, end.z);
    glEnd();
    
    glBegin(GL_QUADS);
    glColor3f(1, 0, 0);
    glNormal3f(normal.x, normal.y, normal.z);
    Point p1 = start + surface; glVertex3f(p1.x, p1.y, p1.z);
    Point p2 = end + surface; glVertex3f(p2.x, p2.y, p2.z);
    Point p3 = end + (surface * -1); glVertex3f(p3.x, p3.y, p3.z);
    Point p4 = start + (surface * -1); glVertex3f(p4.x, p4.y, p4.z);
    glEnd();
    
    glPopMatrix();
}

void Path::update(SDL_Event event){
    
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

