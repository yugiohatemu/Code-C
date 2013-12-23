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
   //idle -> ball enter -> start animation ->animation done, change ball color -> ball leave
    enum State{
        IDLE,
        BALL_ENTER,
        ANIME,
        BALL_LEAVE,
    };
    State state;
public:
    FlipColorPath();
    ~FlipColorPath();
    void render();
    void update(SDL_Event event);
    
    Vector get_normal();
    Matrix get_transform();
    bool is_on_surface(Point p);

};

#endif /* defined(__Code_C__flipColorPath__) */
