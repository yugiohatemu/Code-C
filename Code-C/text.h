//
//  text.h
//  Code-C
//
//  Created by Yue on 1/14/14.
//  Copyright (c) 2014 Yue. All rights reserved.
//

#ifndef __Code_C__text__
#define __Code_C__text__

#include "sprite.h"
#include <string>

class Text:public Sprite{
    std::string s;
public:
    Text(std::string s);
    ~Text();
    void render();
    void update(SDL_Event event);
};

#endif /* defined(__Code_C__text__) */
