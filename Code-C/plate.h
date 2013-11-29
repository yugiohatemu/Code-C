//
//  plate.h
//  Code-C
//
//  Created by Yue on 11/29/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#ifndef __Code_C__plate__
#define __Code_C__plate__


#include "sprite.h"
#include "point.h"
#include "color.h"
class Plate:public Sprite{
    Point corner[4]; //or use bot_top_left_right
    Point normal;
    Color color;
public:
    void render();
    void update(SDL_Event event);

};

#endif /* defined(__Code_C__plate__) */
