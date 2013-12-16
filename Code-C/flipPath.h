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
    std::vector<Path*> next_path;
    std::vector<Vector> next_rotate;
    
    Vector cur_rotate;
    int cur_index = 0;

    enum State{
        STATIC,
        ANIME
    };
    State state;
    
public:
    FlipPath(Vector trans, std::vector<Vector> next_list);
    ~FlipPath();
    
    void add_next_path(Path * p);
    std::vector<Point> get_end_point_list();
    
    //Parent
    Matrix get_transform();
    Vector get_normal();

    bool is_on_surface(Point p);
    
    void render();
    void update(SDL_Event event);
    
    StopWatch timer;
};

#endif /* defined(__Code_C__flipPath__) */