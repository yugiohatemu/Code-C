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
#include "algebra.h"
#include "SDL/SDL_opengl.h"
class Shape{
   //actually, shape is only concerned with
    //which gldisplay list we should call
    //and how are we going to animate it?
    Vector rotate, scale, trans;
    float orien;
    GLuint call_list;
public:
    Shape();
    ~Shape();
    virtual void render() = 0;
    virtual void update(SDL_Event event) = 0;
    typedef std::string ShapeType;
    ShapeType get_shape_type();
protected:
    ShapeType shape_type;
};

#endif /* defined(__Code_C__shape__) */
