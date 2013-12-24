//
//  scene.h
//  Code-C
//
//  Created by Yue on 12/11/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#ifndef __Code_C__scene__
#define __Code_C__scene__

#include "sprite.h"

class Protagonist;
class Path;

class Scene:public Sprite{
    
    Protagonist * pro;
    Path * path;
    void new_scene();
    void delete_scene();
public:

    Scene();
    ~Scene();
    void render();
    void update(SDL_Event event);
    
};


#endif /* defined(__Code_C__scene__) */
