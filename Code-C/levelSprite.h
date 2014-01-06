//
//  levelSprite.h
//  Code-C
//
//  Created by Yue on 12/27/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#ifndef __Code_C__levelSprite__
#define __Code_C__levelSprite__

#include "sprite.h"

class Shape;

class LevelSprite:public Sprite{
    bool selected;
    float orien;
    Shape * shape;
public:
    LevelSprite();
    ~LevelSprite();
    void set_selected(bool s);
    void render();
    void update(SDL_Event event);
};

#endif /* defined(__Code_C__levelSprite__) */
