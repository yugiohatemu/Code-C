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
    Vector normal;
    Matrix prod;
    
public:
    
    Path(Vector trans, Vector scale, Vector roatate);
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
    Matrix get_transform();
};

void delete_path(Path * p);
void render_path(Path * p);


#endif /* defined(__Code_C__path__) */
