//
//  arrowShape.cpp
//  Code-C
//
//  Created by Yue on 1/3/14.
//  Copyright (c) 2014 Yue. All rights reserved.
//

#include "arrowShape.h"
#include "SDL/SDL_opengl.h"

ArrowShape::ArrowShape():Shape(){
    //we should have an arrow prefix or suffix
    //this can be done using string checking easily
    vertexs[1] = Point(-0.3,0,-0.3);
    vertexs[2] = Point(0,0,1);
    vertexs[3] = Point(0.3,0,-0.3);
    //this is forward_arrow
    //we also have backward_arrow
    //and more arrow shapes?
}

ArrowShape::~ArrowShape(){
    
}

////////////////////////////////////////////////////////////////////////////////////////

void ArrowShape::render(){
   //we don't need that for now, because the path will have the matrix ready, we just draw and animate things here
    glNormal3f(0, 1, 0);
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <4 ; i++) {
        glVertex3f(vertexs[i].x, vertexs[i].y, vertexs[i].z);
    }
    glEnd();
    
}

void ArrowShape::update(SDL_Event event){
    //rotate around its own axis?
    //what should we update?
    //My prime idea is actually
    //we just create a shape, get an ID something, and then the shape_factory will draw
    //or call the list that based on our request
    //if so , we need to have a master loader to care about all the shapes
    // which should be shape itself?
    
}