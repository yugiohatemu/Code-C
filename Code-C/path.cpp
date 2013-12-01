//
//  path.cpp
//  Code-C
//
//  Created by Yue on 11/30/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "path.h"
#include "SDL/SDL_opengl.h"

Path::Path(Point start, Point end):start(start), end(end){
    to_next = start - end;
    to_next.normalize();
    to_prev = to_next * -1;
    prev = next = NULL;
}

Path::~Path(){
    prev = next = NULL;
}

void Path::render(){
    
    glBegin(GL_LINES);
    glColor3f(1, 0, 0);
    glVertex3f(start.x, start.y, start.z);
    glVertex3f(end.x, end.y, end.z);
    glEnd();
}

void Path::update(SDL_Event event){
    
}

////////////////////////////////////////////////////////////////////////////////////////////////

Path* create_path(std::vector<Point> point_list){
    //invalid path
    if (point_list.size() < 2) return NULL;
    
    Path * head = new Path(point_list[0],point_list[1]);
    Path * prev = head;
    for (int i = 1; i < point_list.size()-1; i+= 1) {
        Path * t = new Path(point_list[i], point_list[i+1]);
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