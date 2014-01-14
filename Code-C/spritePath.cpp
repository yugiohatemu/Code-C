//
//  spritePath.cpp
//  Code-C
//
//  Created by Yue on 1/14/14.
//  Copyright (c) 2014 Yue. All rights reserved.
//

#include "spritePath.h"

SpritePath::SpritePath():Path(){
    
}

SpritePath::~SpritePath(){
}

/////////////////////////////////////////////////////////////////////////////////////////
Vector SpritePath::get_normal(){
    return normal;
}

Matrix SpritePath::get_transform(){
    return prod;
}

Path::PathType SpritePath::get_path_type(){
    return "SpritePath";
}

/////////////////////////////////////////////////////////////////////////////////////////
void SpritePath::render(){
    
}

void SpritePath::update(SDL_Event event){
    
}

