//
//  track.h
//  Code-C
//
//  Created by Yue on 11/28/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#ifndef __Code_C__track__
#define __Code_C__track__

//one track for a continuous one?
#include "sprite.h"
#include "plate.h"
#include <vector>

class Track:public Sprite{
    std::vector<Plate> platelist;
public:
    Track();
    ~Track();
    void render();
    void update(SDL_Event event);
};

#endif /* defined(__Code_C__track__) */
