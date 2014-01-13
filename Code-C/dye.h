//
//  dye.h
//  Code-C
//
//  Created by Yue on 1/9/14.
//  Copyright (c) 2014 Yue. All rights reserved.
//

#ifndef __Code_C__dye__
#define __Code_C__dye__

#include "sprite.h"
#include "colorRule.h"
#include "algebra.h"

class Dye:public Sprite{
    Color c;
public:
    Dye(ColorRule::State s);
    ~Dye();
    Dye* copy();
    
    void render() ;
    void update(SDL_Event event);
    
    ColorRule::State color_state;
    
};

#endif /* defined(__Code_C__dye__) */
