//
//  pathParser.h
//  Code-C
//
//  Created by Yue on 12/25/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#ifndef Code_C_pathParser_h
#define Code_C_pathParser_h

#include <string>

class Parser{
public:
    virtual Parser(){};
    virtual Parser* parse_from_string(std::string s) = 0;
};

#endif
