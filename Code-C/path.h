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
private:
    Point start, end;
    Vector to_next, to_prev;
    Vector normal; //angel of the plane!
    Vector surface;
    //a lazy way to store angels
    //actually we have 3 angels
    //though I would definately like to approximate them to int
public:
    Path(Point start, Point end, Vector normal);
    ~Path();
    void render();
    void update(SDL_Event event);
    
    Path * prev;
    Path * next;
    
    Vector get_to_next();
    Vector get_to_prev();
    Vector get_normal();
    Point get_end();
    Point get_start();
    Point get_angle();
    
    Point angle;
};

Path* create_path(std::vector<Point> point_list,std::vector<Vector> normal_list);
Path* create_path(std::vector<Point> point_list, std::vector<Vector> normal_list, std::vector<Point> angle_list);
void delete_path(Path * p);
void render_path(Path * p);


#endif /* defined(__Code_C__path__) */
