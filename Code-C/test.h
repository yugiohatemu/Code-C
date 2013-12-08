//
//  test.h
//  Code-C
//
//  Created by Yue on 12/7/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#ifndef __Code_C__test__
#define __Code_C__test__

#include "sprite.h"
#include "algebra.h"

class Prim:public Sprite{
    
public:
    Point start;
    Vector rotate;
    Vector translate;
    Point end;
    Vector normal;
    Vector scale;
    float angle;
    Matrix prod;
    Prim();
    void to_test();
    void render();
    void update(SDL_Event event);
};

#endif /* defined(__Code_C__test__) */
