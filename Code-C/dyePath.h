//
//  dyePath.h
//  Code-C
//
//  Created by Yue on 1/9/14.
//  Copyright (c) 2014 Yue. All rights reserved.
//

#ifndef __Code_C__dyePath__
#define __Code_C__dyePath__

#include "spritePath.h"

class Dye;

class DyePath:public SpritePath{
    Dye * dye;
public:
    DyePath(Point trans, Vector rotate, ColorRule::State dye_color); //add color? and dye color?
    ~DyePath();
//    Dye * get_dye();
    Sprite * give_sprite();
    
    void render();
    void update(SDL_Event event);
    
    Vector get_normal();
    Matrix get_transform();
    PathType get_path_type();
    
};

#endif /* defined(__Code_C__dyePath__) */
