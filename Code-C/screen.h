//
//  screen.h
//  Code-C
//
//  Created by Yue on 12/23/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#ifndef Code_C_screen_h
#define Code_C_screen_h

#include "sprite.h"

class Screen:public Sprite{
protected:
    Screen * root;
public:
    Screen(){};
    virtual ~Screen(){root = NULL;};
    virtual void render() = 0;
    virtual void update(SDL_Event event) = 0;
    void set_controller(Screen * s){
        root = s;
    }
};

#endif
