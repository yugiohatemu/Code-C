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
    
public:
    Path(Point start, Point end);
    ~Path();
    void render();
    void update(SDL_Event event);
    
    Path * prev;
    Path * next;
};

Path* create_path(std::vector<Point> point_list);
void delete_path(Path * p);


#endif /* defined(__Code_C__path__) */
