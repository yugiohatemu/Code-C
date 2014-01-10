//
//  dyePath.h
//  Code-C
//
//  Created by Yue on 1/9/14.
//  Copyright (c) 2014 Yue. All rights reserved.
//

#ifndef __Code_C__dyePath__
#define __Code_C__dyePath__

#include "path.h"

class DyePath:public Path{
public:
    DyePath(Point trans, Vector rotate); //add color? and dye color?
    ~DyePath();
    Vector get_normal();
    Matrix get_transform();
    void render();
    void update(SDL_Event event);
    
};

#endif /* defined(__Code_C__dyePath__) */
