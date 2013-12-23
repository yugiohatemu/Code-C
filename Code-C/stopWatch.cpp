//
//  stopWatch.cpp
//  ForScience
//
//  Created by Yue on 7/20/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "stopWatch.h"
#include "SDL/SDL_timer.h"

StopWatch::StopWatch(){
    count_down = 0;
}

StopWatch::StopWatch(float count_down){
    this->count_down = count_down * 1000;
}

StopWatch::~StopWatch(){
    
}

bool StopWatch::is_timeup(){
    time_accum = time_accum +  SDL_GetTicks() - start_tick;
    start_tick = SDL_GetTicks();
    return (time_accum >= count_down);
}

void StopWatch::start(){
    time_accum = 0;
    start_tick = SDL_GetTicks();
}

float StopWatch::get_accum_time(){
    return time_accum;
}

void StopWatch::reset(){
    time_accum = 0;
}

