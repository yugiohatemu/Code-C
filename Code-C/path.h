//
//  path.h
//  Code-C
//
//  Created by Yue on 11/30/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#ifndef __Code_C__path__
#define __Code_C__path__

#include "algebra.h"
#include "sprite.h"
#include <vector>
#include "color.h"
#include "colorRule.h"

class Path:public Sprite{
protected:
    Point start, end;
    Point vertexs[8];
    Vector normals[6];
    
    Vector to_next, to_prev;
    Vector normal;
    Matrix prod;
    
    //Constructor used by subclass only
    Path();
    
public:
    
    Path(Point trans, Vector scale, Vector roatate);
    ~Path();
    Color c;
    ColorRule::State color_state;
    bool is_ball_on = false;
   
    virtual void render();
    virtual void update(SDL_Event event);
    
    Point get_end();
    Point get_start();
    bool is_path_color_valid();
    
    Path * prev;
    Path * next;

    virtual Vector get_normal();
    virtual Matrix get_transform();
    
    Point get_length_point();
    bool is_on_surface(Point p);
    
    static void delete_path(Path * root);
    static void link_path(Path * p, Path * n);
    static void unlink_path(Path * p, Path * n);
    static Path* end_of_path(Path *p);

};




#endif /* defined(__Code_C__path__) */
