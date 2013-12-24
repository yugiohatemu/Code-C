//
//  screenController.cpp
//  Code-C
//
//  Created by Yue on 12/23/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "screenController.h"

ScreenController::ScreenController(Screen * s):Screen(){
    root.push(s);
    top = root.top();
    top->set_controller(this);
}

ScreenController::~ScreenController(){
    //pop everything
    while (!root.empty()) {
        root.pop();
    }
    top = NULL;
}

void ScreenController::push_controller(Screen * next){
    root.push(next);
    next->set_controller(this);
    top = next;
}

void ScreenController::pop_controller(){
    if (root.size() > 1) {
        root.pop();
        top = root.top();
    }
    //do not allow root to be poped
    //deallocated automatically
}

//keeps pop the controller so that s is the top
void ScreenController::pop_controller_to(Screen * s){
    if (s == NULL) return;
    
    while (root.size()>1){
        if (top != s) {
            pop_controller();
        }else{
            pop_controller();
            break;
        }
    }
}

//////////////////////////////////////////////////////////////////////
//Sprite
void ScreenController::render(){
    top->render();
}

void ScreenController::update(SDL_Event event){
    top->update(event);
}

