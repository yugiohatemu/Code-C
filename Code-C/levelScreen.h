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

class Protagonist;
class Path;

class LevelScreen:public Screen{
    Protagonist * pro;
    Path * path;
public:
    LevelScreen();
    ~LevelScreen();
    void render();
    void update(SDL_Event event);
    void win();
};

#endif /* defined(__Code_C__levelScreenController__) */
