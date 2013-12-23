//
//  stopWatch.h
//  ForScience
//
//  Created by Yue on 7/20/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#ifndef __ForScience__stopWatch___
#define __ForScience__stopWatch___

class StopWatch{
private:
    float time_accum;
    int start_tick;
    float count_down;
public:
    StopWatch();
    StopWatch(float count_down);
    ~StopWatch();
    bool is_timeup();
    void start();
    void reset();
    float get_accum_time();
};


#endif /* defined(__ForScience__stopWatch___) */
