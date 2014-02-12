//
//  stickman.h
//  Code-C
//
//  Created by Yue on 1/16/14.
//  Copyright (c) 2014 Yue. All rights reserved.
//

#ifndef __Code_C__stickman__
#define __Code_C__stickman__

#include "sprite.h"
#include "colorRule.h"
//and stick man has conversation system
//text.
class Stickman:public Sprite{
    
public:
    Stickman();
    ~Stickman();
    void render();
    void update(SDL_Event event);
};

#endif /* defined(__Code_C__stickman__) */
