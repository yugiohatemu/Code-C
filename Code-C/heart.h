//
//  heart.h
//  Code-C
//
//  Created by Yue on 2/12/14.
//  Copyright (c) 2014 Yue. All rights reserved.
//

#ifndef __Code_C__heart__
#define __Code_C__heart__

#include "sprite.h"
#include "colorRule.h"


//he can either be owned by protagonist/path/stickman
//so technically sprite type...I hate casting
class Heart:public Sprite{ //will be more generalize later,like flower, heart, football
    Sprite * owner; //the ownership
    
public:
    Heart();
    ~Heart();
    void render();
    void update(SDL_Event event);
    void set_owner(Sprite * o);
    Color c;
    ColorRule::State color_state;
};

#endif /* defined(__Code_C__heart__) */
