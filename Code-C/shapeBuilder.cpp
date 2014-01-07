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

void ShapeBuilder::load_stl(Shape::ShapeType type){
    std::fstream file;
    file.open(get_absolute_path(type) + ".stl", std::ios::in | std::ios::out | std::ios::binary);
    if (file.fail()) {
        debug("File open error");
        return;
    }
    
    //based on stl format, we ignore the 1st 80 byte generally
    uint8_t header[80]; file.read(reinterpret_cast<char *>(&header), sizeof(header));
    
    uint32_t tri_count;
    file.read(reinterpret_cast<char*>(&tri_count), sizeof(tri_count));
    
    GLuint id = glGenLists(1);
    glNewList(id, GL_COMPILE);
    
    glBegin(GL_TRIANGLES);
    
    for (uint32_t tri = 0; tri < tri_count; tri++) {
        //For every triangle, 1 normal and 3 vertex and 1 attr
        float normal[3];
        for (int i = 0; i < 3; i++){
            file.read(reinterpret_cast<char *>(&normal[i]), sizeof(normal[i]));
//            if (normal[i] < 0.00001f) normal[i] = 0;
        }
        glNormal3fv(normal);
        //3 vertexs
        for (int i = 0; i < 3; i++) {
            float vertex[3];
            for (int j = 0; j < 3; j++) file.read(reinterpret_cast<char *>(&vertex[j]), sizeof(vertex[j]));
            glVertex3fv(vertex);
        }
        
        //ignored for now,might be color
        uint16_t attr; file.read(reinterpret_cast<char *>(&attr), sizeof(attr));
    }
    
    glEnd();
    glEndList();
    
    shape_map[type] = id;
    file.close();

}


void ShapeBuilder::init(){
    
    load_stl("Rect"); //1
    load_stl("Diamond"); //2
    load_stl("Hexagon");//3
    load_stl("Arrow"); //4
    load_stl("Triangle"); //5
    
}

void ShapeBuilder::clear(){
    for (std::map<Shape::ShapeType, GLuint>::iterator it = shape_map.begin(); it != shape_map.end(); it++) {
        glDeleteLists((*it).second, 1);
    }
}

GLuint ShapeBuilder::get_list_id(Shape::ShapeType type){
    if(shape_map.find(type) != shape_map.end()){
        return shape_map[type];
    }
    return 0;
}