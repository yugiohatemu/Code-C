//
//  shape.cpp
//  Code-C
//
//  Created by Yue on 1/3/14.
//  Copyright (c) 2014 Yue. All rights reserved.
//

#include "shape.h"
#include "SDL/SDL_opengl.h"

Shape::Shape(){
    
}

Shape::~Shape(){
    
}

//////////////////////////////////////////////////////////////////////////////////////////
//Sprite interface
void Shape::render(){
    
}
void Shape::update(SDL_Event event){
    
}

//////////////////////////////////////////////////////////////////////////////////////////

Shape::ShapeType Shape::get_shape_type(){
    return shape_type;
}