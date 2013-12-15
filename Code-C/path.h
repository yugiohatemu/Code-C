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

class Path:public Sprite{
protected:
    Point start, end;
    Point vertexs[8];
    Vector normals[6];
    
    Vector to_next, to_prev;
    Vector normal;
    Matrix prod;
    //Only used by subclass
    Path();
    Path * prev;
    Path * next;
public:
    
    Path(Vector trans, Vector scale, Vector roatate);
    ~Path();
    virtual void render();
    virtual void update(SDL_Event event);
    
    Point get_end();
    Point get_start();
    void set_next_path(Path * p);
    void set_prev_path(Path * p);
    
    virtual Path * get_prev_path();
    virtual Path * get_next_path();
    virtual Vector get_normal();
    virtual Matrix get_transform();
    
    Point get_length_point();
    bool is_on_surface(Point p);
    
    static void delete_path(Path * root);
    static Path* make_consecutive_path(Vector start, std::vector<Vector> trans_list);
};




#endif /* defined(__Code_C__path__) */
