//
//  shape.h
//  Code-C
//
//  Created by Yue on 1/3/14.
//  Copyright (c) 2014 Yue. All rights reserved.
//

#ifndef __Code_C__shape__
#define __Code_C__shape__

#include "sprite.h"
#include <string>

class Shape{
   //actually, shape is only concerned with
    //which gldisplay list we should call
    //and how are we going to animate it?

public:
    Shape();
    ~Shape();
    virtual void render();
    virtual void update(SDL_Event event);
    typedef std::string ShapeType;
    ShapeType get_shape_type();
protected:
    ShapeType shape_type;
};

#endif /* defined(__Code_C__shape__) */
