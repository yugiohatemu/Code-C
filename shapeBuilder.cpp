//
//  shapeBuilder.cpp
//  Code-C
//
//  Created by Yue on 1/3/14.
//  Copyright (c) 2014 Yue. All rights reserved.
//

#include "shapeBuilder.h"
#include "utility.h"
#include <vector>
#include <fstream>

ShapeBuilder::ShapeBuilder(){
    
}
ShapeBuilder::ShapeBuilder(ShapeBuilder const &){
    
}

ShapeBuilder& ShapeBuilder::operator= (ShapeBuilder const &){
    return *this;
}

ShapeBuilder& ShapeBuilder::Instance(){
    static ShapeBuilder m_Instance;
    return m_Instance;
}

//////////////////////////////////////////////////////////////////////////////



void ShapeBuilder::init(){
    
    Shape::ShapeType s = "rect";
    std::fstream file;
    file.open(get_absolute_path(s) + ".stl", std::ios::in | std::ios::out | std::ios::binary);
    if (file.fail()) {
        debug("File open error");
        return;
    }
   
    //based on stl format, we ignore the 1st 80 byte generally
    uint8_t header[80];
    file.read(reinterpret_cast<char *>(&header), sizeof(header));
    
    uint32_t tri_count;
    file.read(reinterpret_cast<char*>(&tri_count), sizeof(tri_count));
 
    glGenLists(1);
    GLuint id = 0;
    glNewList(id, GL_COMPILE);
    glBegin(GL_TRIANGLES);
    
    for (uint32_t tri = 0; tri < tri_count; tri++) {
        //For every triangle, 1 normal and 3 vertex and 1 attr
        float normal[3];
        for (int i = 0; i < 3; i++) file.read(reinterpret_cast<char *>(&normal[i]), sizeof(normal[i]));
        glNormal3fv(normal);
        
        for (int i = 0; i < 3; i++) {
            float vertex[3];
            for (int j = 0; j < 3; j++) file.read(reinterpret_cast<char *>(&vertex[j]), sizeof(vertex[j]));
            glVertex3fv(vertex);
        }
        
        //ignored for now,might be color
        uint16_t attr;
        file.read(reinterpret_cast<char *>(&attr), sizeof(attr));
    }
    
    glEnd();
    glEndList();
    
    shape_map[s] = id;
    
    file.close();
}

void ShapeBuilder::clear(){
    for (std::map<Shape::ShapeType, GLuint>::iterator it; it != shape_map.end(); it++) {
        glDeleteLists((*it).second, 1);
    }
}

GLuint ShapeBuilder::get_list_id(Shape::ShapeType type){
    if(shape_map.find(type) != shape_map.end()){
        return shape_map[type];
    }
    return 0;
}