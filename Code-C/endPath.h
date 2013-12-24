//
//  endPath.h
//  Code-C
//
//  Created by Yue on 12/23/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#ifndef __Code_C__endPath__
#define __Code_C__endPath__

#include "path.h"

class EndPath:public Path{
    
public:
    EndPath(Vector trans, Vector rotate);
    ~EndPath();
    
    void render();
    void update(SDL_Event event);
    Vector get_normal();
    Matrix get_transform();
    bool is_on_surface(Point p);

};

#endif /* defined(__Code_C__endPath__) */
