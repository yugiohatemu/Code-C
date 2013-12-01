//
//  sprite.h
//  Trilight
//
//  Created by Yue on 10/11/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#ifndef __Trilight__sprite__
#define __Trilight__sprite__

#include "SDL/SDL_events.h"

//pure virtual class for basic drawing and accepting user input
class Sprite{

public:

    virtual ~Sprite(){};

    virtual void render() = 0;
    virtual void update(SDL_Event event) = 0;
    
};

#endif /* defined(__Trilight__sprite__) */
