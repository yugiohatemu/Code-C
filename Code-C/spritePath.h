//
//  spritePath.h
//  Code-C
//
//  Created by Yue on 1/14/14.
//  Copyright (c) 2014 Yue. All rights reserved.
//

#ifndef __Code_C__spritePath__
#define __Code_C__spritePath__

#include "path.h"

class SpritePath:public Path{
    Sprite * sprite;
public:
    SpritePath(Point trans, Vector rotate);
    ~SpritePath();
    
    void render();
    void update(SDL_Event event);
    
    Vector get_normal();
    Matrix get_transform();
    PathType get_path_type();
    
    virtual Sprite * give_sprite();
    void set_sprite(Sprite * s);
};

#endif /* defined(__Code_C__spritePath__) */
