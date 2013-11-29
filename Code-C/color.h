//
//  color.h
//  Code-C
//
//  Created by Yue on 11/29/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#ifndef __Code_C__color__
#define __Code_C__color__

struct Color{
    float r, g, b, a;
    Color();
    Color(float r, float g,float b,float a = 1.0f);
    Color(float c);
    Color(const Color & c);
    Color& operator =(const Color& c);
    //add short cut for black 
};

#endif /* defined(__Code_C__color__) */
