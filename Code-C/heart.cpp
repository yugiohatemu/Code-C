//
//  heart.cpp
//  Code-C
//
//  Created by Yue on 2/12/14.
//  Copyright (c) 2014 Yue. All rights reserved.
//

#include "SDL/SDL_opengl.h"
#include "heart.h"
#include "spritePath.h"
#include "protagonist.h"
#include "stickman.h"

Heart::Heart(){
    owner = NULL;
}

Heart::~Heart(){
    owner = NULL; //the owner will take responsibility of clean up
}

void Heart::set_owner(Sprite * o){
    //ask previous owner to unset itself
//    SpritePath * owned_path= dynamic_cast<SpritePath *>(owner);
//    if (owned_path) {
//        owned_path->set_sprite(NULL);
//        owner = o;
//        return ;
//    }
//    
//    Protagonist * owned_pro = dynamic_cast<Protagonist *>(owner);
//    if (owned_pro) {
//        owned_pro->set_sprite(NULL);
//        owner = o;
//        return ;
//    }
    
    owner = o;
    
}


////////////////////////////////////////////////////////////////////////////
void Heart::render(){
    //who ever owns him will do parent transformation
    if (!ColorRule::Instance().is_state_global(color_state)) return;
    
    glPushMatrix();
    glColor3f(1, 1, 0);
    
    //use a square/cube/tetlehedron
    glBegin(GL_TRIANGLES);
    glNormal3f(0, 1, 0); glVertex3f(0.5, 0, 0); glVertex3f(0, 0, -0.3); glVertex3f(0, 0, 0.3);
    glNormal3f(0, 1, 0); glVertex3f(0.5, 0, 0); glVertex3f(0.8, 0, -0.3); glVertex3f(0.8, 0, 0.3);
    glEnd();
    
    glPopMatrix();
}

void Heart::update(SDL_Event event){
    //whoever owns it is respobsible of updating it
    //also used for animation if there is any
}

//