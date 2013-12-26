//
//  parseError.h
//  Code-C
//
//  Created by Yue on 12/25/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#ifndef Code_C_parseError_h
#define Code_C_parseError_h

#include <iostream>
#include <exception>

class ParseError:public exception{
    std::string reason;
public:
    ParseError(std::string s):reason(s){};
    
    virtual const char* what() const throw(){
        return reason;
    }
};

#endif
