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
#include "color.h"
#include "algebra.h"

class Plate:public Sprite{
    Point top_left, top_right, bot_left, bot_right;
    Vector normal;
    Color color;
public:
    Plate();
    Plate(Point tl, Point tr, Point bl, Point br, Vector n, Color c);
    ~Plate();
    void render();
    void update(SDL_Event event);

};

#endif /* defined(__Code_C__plate__) */
