//
//  levelScreenController.cpp
//  Code-C
//
//  Created by Yue on 12/24/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "levelScreen.h"
#include "scene.h"

LevelScreen::LevelScreen():Screen(){
    scene = new Scene();
}

LevelScreen::~LevelScreen(){
    delete scene;
}

//////////////////////////////////////////////////
//Sprite interface
void LevelScreen::render(){
    scene->render();
}

void LevelScreen::update(SDL_Event event){
    scene->update(event);
}