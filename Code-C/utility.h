//
//  utility.h
//  Code-C
//
//  Created by Yue on 12/2/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#ifndef __Code_C__utility__
#define __Code_C__utility__
#include <iostream>

template<class NUM>
bool is_num_whithin(NUM n, NUM a, NUM b){
    return (a <= n && n <= b) || (b <= n && n <= a) ;
}

template<class PRINT>
void debug(PRINT s){
    std::cout<<"DEBUG: "<<s<<std::endl;
}

template<class CNUM>
CNUM clamp(CNUM n, CNUM a, CNUM b){
    CNUM small = std::min(a, b);
    CNUM big = std::max(a,b);
    if (is_num_whithin(n,a,b)) return n;
    else if (n < small) return small;
    else return big;
}


std::string readFile(std::string filename);
int printOglError(char *file, int line);
void printShaderInfoLog(GLuint obj);
void printProgramInfoLog(GLuint obj);

#endif /* defined(__Code_C__utility__) */
