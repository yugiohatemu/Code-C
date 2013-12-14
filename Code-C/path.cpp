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


Path::Path(Vector trans, Vector rotate, Vector scale){
    
    //seperate scale matrix from directional matrix
    vertexs[0] = Point(0, 0, -0.5);vertexs[1] = Point(0, 0, 0.5); //we force it to be zero to save translation
    vertexs[2] = Point(1, 0, 0.5);vertexs[3] = Point(1, 0, -0.5);
    for (int i = 4; i < 8; i++) {
        vertexs[i] = vertexs[i-4]; vertexs[i].y = -0.1;
    }
    normals[0] = Vector(0, 1, 0); normals[1] = Vector(0, -1, 0);
    normals[2] = Vector(0, 0, 1); normals[3] = Vector(0, 0, -1);
    normals[4] = Vector(1, 0, 0); normals[5] = Vector(-1, 0, 0);
    
    for (int i = 0; i < 8; i++) vertexs[i] = Matrix::scale(scale) * vertexs[i];
    start = Point::get_mid(vertexs[0], vertexs[1]);
    end = Point::get_mid(vertexs[2], vertexs[3]);
    
    //rotate on the start point
    prod = Matrix::translate(trans)
    * Matrix::roatate(Vector(1,0,0), rotate.x)
    * Matrix::roatate(Vector(0,1,0), rotate.y)
    * Matrix::roatate(Vector(0,0,1), rotate.z);
    
    end = prod * end;
    start = prod * start;
    normal = prod * Vector(0,1,0); normal.normalize();

    //for a single , it is right for now
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
    glColor3f(1, 0, 0);
    glMultMatrixf(prod.begin());
    glBegin(GL_QUADS);
    
    for (int i = 0; i < 6; i++) {
        glNormal3f(normals[i].x, normals[i].y, normals[i].z);
        for (int j = 0; j < 4; j++) {
            int index = indices[4*i+j];
            glVertex3f(vertexs[index].x, vertexs[index].y, vertexs[index].z);
        }
    }
    
    glEnd();
    glPopMatrix();

    
//    glPushMatrix();
//    glBegin(GL_LINES);
//    glColor3f(0, 0, 0);
//    glVertex3f(start.x, start.y, start.z); glVertex3f(end.x, end.y, end.z);
//    glEnd();
//    glPopMatrix();

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

Point Path::get_length_point(){
    return Point::get_mid(vertexs[2], vertexs[3]);
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
        Point p = prev->get_end();
        Vector next_start(p.x,p.y,p.z);
        //so translate to start first, rotate, then translate back?
        Path * next = new Path(next_start, trans_list[i], trans_list[i+1]);
        
        prev->next = next;
        next->prev = prev;
        prev = next;
        
    }
    
    return head;
}

//I understand how draw array work..
//but what about draw element?

//GLfloat vertices[] = {
//    0, 0, -0.5,  0, 0, 0.5,  0, -0.1, -0.5,   0, -0.1, 0.5,   // 0, 1, 4, 5 (front)
//    0, 0, 0.5,   1, 0, 0.5,  1, -0.1, 0.5,   0, -0.1, 0.5,   // 1, 2, 6, 5 (right)
//    0, 0, -0.5,   0, 0, 0.5,  1, 0, 0.5,  1, 0, -0.5,   // 0, 1, 2, 3 (top)
//    0, 0, -0.5,  1, 0, -0.5,  1, -0.1, -0.5,  0, -0.1, -0.5,   // 0, 3, 7, 4 (left)
//    0, -0.1, -0.5,   0, -0.1, 0.5,   1, -0.1, 0.5,  1, -0.1, -0.5,   // 4, 5, 6, 7 (bottom)
//    1, 0, 0.5,  1, 0, -0.5,  1, -0.1, -0.5,   1, -0.1, 0.5 }; // 2, 3, 7, 6 (back)
//
//// normal array
//GLfloat normals[]  = { 0, 0, 1,   0, 0, 1,   0, 0, 1,   0, 0, 1,   // 0, 1, 4, 5 (front)
//    1, 0, 0,   1, 0, 0,   1, 0, 0,   1, 0, 0,   // 1, 2, 6, 5 (right)
//    0, 1, 0,   0, 1, 0,   0, 1, 0,   0, 1, 0,   // v0,v5,v6,v1 (top)
//    -1, 0, 0,  -1, 0, 0,  -1, 0, 0,  -1, 0, 0,   // v1,v6,v7,v2 (left)
//    0,-1, 0,   0,-1, 0,   0,-1, 0,   0,-1, 0,   // v7,v4,v3,v2 (bottom)
//    0, 0,-1,   0, 0,-1,   0, 0,-1,   0, 0,-1 }; // v4,v7,v6,v5 (back)
//
//// index array of vertex array for glDrawElements() & glDrawRangeElement()
//GLubyte indices[]  = { 0, 1, 2,   2, 3, 0,      // front
//    4, 5, 6,   6, 7, 4,      // right
//    8, 9,10,  10,11, 8,      // top
//    12,13,14,  14,15,12,      // left
//    16,17,18,  18,19,16,      // bottom
//    20,21,22,  22,23,20 };    // back


//use gldrawarray later
//    glEnableClientState(GL_VERTEX_ARRAY);
//    glEnableClientState(GL_NORMAL_ARRAY);
//
//    glColor3f(1, 0, 0);
//    glNormalPointer(GL_FLOAT, 0, normals);
//    glVertexPointer(3, GL_FLOAT, 0, vertices);
//
//    glPushMatrix();
//    glMultMatrixf(prod.begin());
//    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, indices);
//    glPopMatrix();
//
//    glDisableClientState(GL_VERTEX_ARRAY);
//    glDisableClientState(GL_NORMAL_ARRAY);
