//
//  protagonist.h
//  Code-C
//
//  Created by Yue on 11/28/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#ifndef __Code_C__protagonist__
#define __Code_C__protagonist__

#include "sprite.h"
#include "algebra.h"
#include "color.h"
#include "colorRule.h"

class Path;
class Dye;

class Protagonist:public Sprite{
    Point anchor;
    Vector orien;
    Color c;
    ColorRule::State color_state;
public:
    
    Protagonist();
    ~Protagonist();
    void render();
    void update(SDL_Event event);
    Path * current;
    Dye * dye;
};

#endif /* defined(__Code_C__protagonist__) */
