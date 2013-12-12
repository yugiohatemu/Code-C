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
    
    Scene();
    Scene(Scene const &);
    Scene& operator= (Scene const &);
    Protagonist * pro;
    Path * path;
public:
    static Scene& Instance();
    
    void render();
    void update(SDL_Event event);
    void new_scene();
    void delete_scene();
};


#endif /* defined(__Code_C__scene__) */
