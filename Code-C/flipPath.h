//
//  flipPath.h
//  Code-C
//
//  Created by Yue on 12/14/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#ifndef __Code_C__flipPath__
#define __Code_C__flipPath__

#include "path.h"
#include "stopWatch.h"

class FlipPath:public Path{
    
    std::vector<Vector> next_rotate;
    
    Vector cur_rotate;
    int cur_index = 0;

    enum State{
        IDLE,
        ANIME
    };
    State state;
    
protected:
    FlipPath();
    std::vector<Path*> next_path;
    
public:
    FlipPath(Point trans, std::vector<Vector> next_list);
    ~FlipPath();
    
    void add_next_path(Path * p);
    std::vector<Point> get_end_point_list();
    
    //Parent
    Matrix get_transform();
    Vector get_normal();
    PathType get_path_type();
    
    void render();
    void update(SDL_Event event);
    
    StopWatch timer;
};

#endif /* defined(__Code_C__flipPath__) */
