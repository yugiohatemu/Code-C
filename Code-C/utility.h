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
#include <vector>
#include "SDL/SDL_opengl.h"
#include "parseError.h"

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

float adjust(float cur, float next, float step);
std::string readFile(std::string filename);
int printOglError(char *file, int line);
void printShaderInfoLog(GLuint obj);
void printProgramInfoLog(GLuint obj);

//Used for string split
std::vector<std::string> split(const std::string &s, char delim);

//Used for loading
std::string get_absolute_path(std::string filename);

//used for base number
int get_int(std::string s) throw (std::exception);

#endif /* defined(__Code_C__utility__) */
