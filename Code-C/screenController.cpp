//
//  screenController.cpp
//  Code-C
//
//  Created by Yue on 12/23/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "screenController.h"

ScreenController::ScreenController(Screen * s):Screen(){
    controller_stack.push(s);
    top = controller_stack.top();
    top->set_controller(this);
}

ScreenController::~ScreenController(){
    //pop everything
    while (!controller_stack.empty()) {
        top = controller_stack.top();
        delete top;
        controller_stack.pop();
    }
    top = NULL;
}

void ScreenController::push_controller(Screen * next){
    controller_stack.push(next);
    next->set_controller(this);
    top = next;
}

void ScreenController::pop_controller(){
    if (controller_stack.size() > 1) {
        delete top;
        controller_stack.pop();
        top = controller_stack.top();
    }
}

//keeps pop the controller so that s is the top
void ScreenController::pop_controller_to(Screen * s){
    if (s == NULL) return;
    
    while (controller_stack.size()>1){
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

