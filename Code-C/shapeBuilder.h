//
//  shapeBuilder.h
//  Code-C
//
//  Created by Yue on 1/3/14.
//  Copyright (c) 2014 Yue. All rights reserved.
//

#ifndef __Code_C__shapeBuilder__
#define __Code_C__shapeBuilder__

#include "shape.h"
#include "SDL/SDL_opengl.h"
#include <map>

class ShapeBuilder{
    ShapeBuilder();
    ShapeBuilder(ShapeBuilder const &);
    ShapeBuilder& operator= (ShapeBuilder const &);
    std::map<Shape::ShapeType, GLuint> shape_map;
    
public:
    static ShapeBuilder& Instance();
    //...I am thinking whether I can just make a base singelton class...for all of them
    void init();
    void clear(); //or call delete
    GLuint get_list_id(Shape::ShapeType type);
};

#endif /* defined(__Code_C__shapeBuilder__) */
