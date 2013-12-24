//
//  flipColorPath.h
//  Code-C
//
//  Created by Yue on 12/22/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#ifndef __Code_C__flipColorPath__
#define __Code_C__flipColorPath__

#include "path.h"

class FlipColorPath:public Path{
   
    enum State{
        IDLE,
        ANIME,
        ANIME_DONE,
    };
    State state;
    
    Vector axis;
    float orien;
public:
    FlipColorPath(Vector trans, Vector rotate); 
    ~FlipColorPath();
    void render();
    void update(SDL_Event event);
    
    Vector get_normal();
    Matrix get_transform();
    bool is_on_surface(Point p);

};

#endif /* defined(__Code_C__flipColorPath__) */
