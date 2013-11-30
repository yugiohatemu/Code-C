//
//  track.cpp
//  Code-C
//
//  Created by Yue on 11/28/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "track.h"
#include "SDL/SDL_opengl.h"

Track::Track(){
    platelist.push_back(Plate(Point(0.0, 0.0,0.0), Point(0.0, 0.0,1.0), Point(2.0, 0.0,0.0), Point(2.0, 0.0,1.0),
                              Vector(0.0,1.0,0.0), Color(1.0, 1.0, 0)));
    platelist.push_back(Plate(Point(2.0, 0.0,1.0), Point(2.0, 0.0,0.0), Point(3.0, 1.0,1.0), Point(3.0, 1.0,0.0),
                              Vector(1, 1, 0), Color(1.0, 1.0, 0)));
    platelist.push_back(Plate(Point(3.0, 1.0,0.0), Point(3.0, 1.0,1.0), Point(2.0, 2.0,0.0), Point(2.0, 2.0,1.0),
                              Vector(1, -1, 0), Color(1.0, 1.0, 0)));
    platelist.push_back(Plate(Point(0.0, 2.0,0.0), Point(0.0, 2.0,1.0), Point(2.0, 2.0,0.0), Point(2.0, 2.0,1.0),
                              Vector(0.0,-1.0,0.0), Color(1.0, 1.0, 0)));
}

Track::~Track(){
    
}

void Track::render(){
    glPushMatrix();
    for (Plate & p : platelist) {
        p.render();
    }
    glPopMatrix();
}

void Track::update(SDL_Event event){
    
}