//
//  pathMaker.h
//  Code-C
//
//  Created by Yue on 12/24/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#ifndef __Code_C__pathMaker__
#define __Code_C__pathMaker__

#include "path.h"

class PathMaker{
public:
    static Path* make_path_from_file(std::string fileName);
};

#endif /* defined(__Code_C__pathMaker__) */
