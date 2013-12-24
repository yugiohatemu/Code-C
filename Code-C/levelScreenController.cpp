//
//  levelScreenController.cpp
//  Code-C
//
//  Created by Yue on 12/24/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "levelScreenController.h"
#include "scene.h"

LevelScreenController::LevelScreenController():Screen(){
    scene = new Scene();
}

LevelScreenController::~LevelScreenController(){
    delete scene;
}

//////////////////////////////////////////////////
//Sprite interface
void LevelScreenController::render(){
    scene->render();
}

void LevelScreenController::update(SDL_Event event){
    scene->update(event);
}