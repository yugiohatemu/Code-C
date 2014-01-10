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

class Dye:public Sprite{
public:
    Dye();
    ~Dye();
    void render() ;
    void update(SDL_Event event);
};

#endif /* defined(__Code_C__dye__) */
