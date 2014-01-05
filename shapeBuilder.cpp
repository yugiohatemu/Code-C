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
    
    std::ifstream file(get_absolute_path("filename"));
    
   
    //will things get delted once out of stack?
    Shape::ShapeType name;
    if (file.is_open()){
        if(getline (file,name)){
            std::vector<Point> vertexs;
            //Q:is this necessary to do that?
            std::string line;
            while ( getline (file,line) ){
                std::vector<std::string> items = split(line, ' ');
                //use a tag, like start or end to mark , even though I think we should count?
                if(items.size()== 4){
                    for (int i = 0; i < 4; i++) {
                        try {
                            vertexs.push_back(Point::get_point_from_string(items[i]));
                        }catch (std::exception & e) {
                            debug(e.what());
                            //TODO：set a flag?
                        }
                    }
                }else{
                    //something is wrong
                    debug("Shape file format error");
                    //TODO: set flag?
                }
            }
        }
        file.close();
    }
    //start parsing file
    
    //name
    //then 1 normal and 3 points loop until we get another name
    //store it in vector, and then clean it
    //it is just easier for me to read, if everything is not in one line
    
    
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