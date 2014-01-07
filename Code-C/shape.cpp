//
//  shape.cpp
//  Code-C
//
//  Created by Yue on 1/3/14.
//  Copyright (c) 2014 Yue. All rights reserved.
//

#include "shape.h"
#include "shapeBuilder.h"

Shape::Shape(){
    //get id
    call_list = ShapeBuilder::Instance().get_list_id("Rect");
    if (call_list == 0) {
        //we get a wrong type
    }
}

Shape::~Shape(){
    
}

//////////////////////////////////////////////////////////////////////////////////////////

Shape::ShapeType Shape::get_shape_type(){
    return shape_type;
}

void Shape::render(){
    glCallList(call_list);
}

void Shape::update(SDL_Event event){
    
}