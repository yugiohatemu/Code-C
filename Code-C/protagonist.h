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
#include "point.h"

class Protagonist:public Sprite{
    Point anchor;
public:
    Protagonist();
    ~Protagonist();
    void render();
    void update(SDL_Event event);
};

#endif /* defined(__Code_C__protagonist__) */
