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
    
    Path(Vector trans, Vector scale, Vector roatate);
    Color c;
    ColorRule::State color_state;
    
    ~Path();
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
    virtual bool is_on_surface(Point p);
    
    static void delete_path(Path * root);
    static void link_path(Path * p, Path * n);
    static void unlink_path(Path * p, Path * n);
    
    static Path* make_consecutive_path(Vector start, std::vector<Vector> trans_list);
    static Path* make_consecutive_path(Vector start, std::vector<Vector> trans_list, Color color);
    

};




#endif /* defined(__Code_C__path__) */
