//
//  sprite.h
//  Trilight
//
//  Created by Yue on 10/11/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#ifndef __Trilight__sprite__
#define __Trilight__sprite__

#include "SDL/SDL.h"
/*
struct T_Rect{
    float x, y,w,h;
    T_Rect(){ x = y = w = h = 0.0f; }
    T_Rect& operator=(T_Rect t){
        x = t.x;
        y = t.y;
        w = t.w;
        h = t.h;
        return *this;
    }
    ~T_Rect(){}
};
*/

class Sprite{

public:

    Sprite(){}
    virtual ~Sprite(){};

    virtual void render() = 0;
    virtual void update(SDL_Event event) = 0;
    
};

#endif /* defined(__Trilight__sprite__) */
