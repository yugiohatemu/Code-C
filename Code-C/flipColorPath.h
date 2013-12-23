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
   //I think maybe we can extend this from flipPath
    enum State{
        IDLE,
        ANIME,
    };
    State state;

    std::vector<Vector> next_rotate;
    std::vector<ColorRule::State> next_color_state;
    Vector cur_rotate;
    int cur_index = 0;
public:
    FlipColorPath(Vector trans, std::vector<Vector> rotate_list, std::vector<ColorRule::State> color_list);
    ~FlipColorPath();
    void render();
    void update(SDL_Event event);
    
    Vector get_normal();
    Matrix get_transform();
    bool is_on_surface(Point p);

};

#endif /* defined(__Code_C__flipColorPath__) */
