//
//  arrowShape.h
//  Code-C
//
//  Created by Yue on 1/3/14.
//  Copyright (c) 2014 Yue. All rights reserved.
//

#ifndef __Code_C__arrowShape__
#define __Code_C__arrowShape__

#include "shape.h"

class ArrowShape:public Shape {
    Point vertexs[4]; //just a surface for now?
    //use a vector for now
public:
    
    ArrowShape();
    ~ArrowShape();
    void render();
    void update(SDL_Event event);
};

#endif /* defined(__Code_C__arrowShape__) */
