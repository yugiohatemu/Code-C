//
//  skybox.h
//  Code-C
//
//  Created by Yue on 1/2/14.
//  Copyright (c) 2014 Yue. All rights reserved.
//

#ifndef __Code_C__skybox__
#define __Code_C__skybox__

#include "sprite.h"
#include "algebra.h"

class Skybox:public Sprite {
    Point center;
   
public:
    Skybox();
    ~Skybox();
    void render();
    void update(SDL_Event event);
};

#endif /* defined(__Code_C__skybox__) */
