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
    
    
    std::fstream file;
    file.open("/Users/wei/Desktop/stlreader/test.stl", std::ios::in | std::ios::out | std::ios::binary);
    if (file.fail()) debug("File open error");
    //based on stl, we ignore the 1st 80 byte?
    uint8_t header[80];
    file.read(reinterpret_cast<char *>(&header), sizeof(header));
    
    //
    do {
        //triangle num
        uint32_t tri_count;
        file.read(reinterpret_cast<char*>(&tri_count), sizeof(tri_count));
        std::cout<<tri_count<<std::endl;
        for (uint32_t i = 0; i < tri_count; i++) {
            //twelve 32-bit-floating point numbers
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 3; j++) {
                    float n;
                    file.read(reinterpret_cast<char *>(&n), sizeof(n));
                    std::cout<<n<<" ";
                }
                std::cout<<std::endl;
            }
            //ignored infact
            uint16_t attr;
            file.read(reinterpret_cast<char *>(&attr), sizeof(attr));
        }
        
        //end
    } while (!file.eof());
    
    file.close();
   
    //create a list of display list
//    glGenLists(1) continuously
   
    //already have arrow(1/2), star(1), rectangle/square(1),diamond,hexagon, triangles
//    glNewList(mysphereID, GL_COMPILE);
//    do something
//    glEndList();

}

void ShapeBuilder::clear(){
    //delte all the call list
}