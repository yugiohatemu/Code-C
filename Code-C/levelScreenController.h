//
//  levelScreenController.h
//  Code-C
//
//  Created by Yue on 12/24/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#ifndef __Code_C__levelScreenController__
#define __Code_C__levelScreenController__

#include "screen.h"

class LevelScreenController{
public:
    LevelScreenController();
    ~LevelScreenController();
    void render();
    void update(SDL_Event event);
};

#endif /* defined(__Code_C__levelScreenController__) */
