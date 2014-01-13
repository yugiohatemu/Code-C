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
    
    int cur_index, next_index;
    Vector axis;
    float cur_orien;
    
    std::vector<ColorRule::State> next_color;
    std::vector<float> next_orien;
public:
    FlipColorPath(Point trans, Vector rotate, std::vector<ColorRule::State> next_color, std::vector<float> next_orien);
    ~FlipColorPath();
    void render();
    void update(SDL_Event event);
    
    Vector get_normal();
    Matrix get_transform();
    PathType get_path_type();
};

#endif /* defined(__Code_C__flipColorPath__) */
