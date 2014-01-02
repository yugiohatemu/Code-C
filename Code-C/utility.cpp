//
//  utility.cpp
//  Code-C
//
//  Created by Yue on 12/2/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "utility.h"
#include <fstream>
#include <sstream>
#include "SDL/SDL_opengl.h"

#ifdef _WIN32
#include <direct.h>
#define getcwd _getcwd // stupid MSFT "deprecation" warning
#else
#include <unistd.h>
#endif

/////////////////////////////////////////////////////////////////////
//routine for clamping cur to next using step
float adjust(float cur, float next, float step){
    if (next >= cur){
        if(next >= cur + step) cur += step;
        else cur = next;
    }else{
        if (next <= cur - step) cur -= step;
        else cur = next;
    }
    return cur;
}

/////////////////////////////////////////////////////////////////////
std::string readFile(std::string filename){
    std::ifstream file(filename.c_str());
    std::string line;
    std::string total = "";
    if (file.is_open()){
        while ( getline (file,line) ){
            total += line;
        }
        file.close();
    }
    //    std::cout<<total<<std::endl;
    
    return total;
}

int printOglError(char *file, int line){
    
    GLenum glErr;
    int retCode = 0;
    //if 0, then correct?
    glErr = glGetError();
    while (glErr != GL_NO_ERROR){
        
        debug(gluErrorString(glErr));
        retCode = 1;
        glErr = glGetError();
    }
    return retCode;
}


void printShaderInfoLog(GLuint obj){
    int infologLength = 0;
    int charsWritten  = 0;
    char *infoLog;
    
    glGetShaderiv(obj, GL_INFO_LOG_LENGTH,&infologLength);
    
    if (infologLength > 0){
        infoLog = (char *)malloc(infologLength);
        glGetShaderInfoLog(obj, infologLength, &charsWritten, infoLog);
        debug(infoLog);
        free(infoLog);
    }
}

void printProgramInfoLog(GLuint obj){
    int infologLength = 0;
    int charsWritten  = 0;
    char *infoLog;
    
    glGetProgramiv(obj, GL_INFO_LOG_LENGTH,&infologLength);
    
    if (infologLength > 0)
    {
        infoLog = (char *)malloc(infologLength);
        glGetProgramInfoLog(obj, infologLength, &charsWritten, infoLog);
        debug(infoLog);
        free(infoLog);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//For string split http://stackoverflow.com/questions/236129/how-to-split-a-string-in-c

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        //Avoid empty token
        if (!item.empty()) elems.push_back(item);
    }
    return elems;
}


std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//Get current working directory
std::string get_absolute_path(std::string filename){
    /*char buffer[256];
    char *answer = getcwd(buffer, sizeof(buffer));
    std::string s_cwd;
    if (answer){
        s_cwd = answer;
        s_cwd +=  "/";
        s_cwd += filename;
        return s_cwd;
    }*/
    std::string all = "/Users/wei/Desktop/Code-C/Code-C/" + filename;
    
    return all;
}

int get_int(std::string s) throw (std::exception){
    int i = 0;
   
    if (!(std::istringstream(s)>>i)){
        throw ParseError("Invalid integer format");
    }
    return i;
}