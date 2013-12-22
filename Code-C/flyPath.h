//
//  flyPath.h
//  Code-C
//
//  Created by Yue on 12/22/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#ifndef __Code_C__flyPath__
#define __Code_C__flyPath__

#include "path.h"

class FlyPath:public Path{
    Vector cur_trans;
public:
    FlyPath(Vector start_trans, Vector end_trans);
    ~FlyPath();
    
    void render();
    void update(SDL_Event event);
    
    Vector get_normal();
    Matrix get_transform();
    bool is_on_surface(Point p);
};

#endif /* defined(__Code_C__flyPath__) */
