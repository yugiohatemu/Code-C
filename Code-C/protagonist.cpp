//
//  protagonist.cpp
//  Code-C
//
//  Created by Yue on 11/28/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "protagonist.h"
#include "SDL/SDL_opengl.h"
#include <GLUT/GLUT.h>
#include "camera.h"
#include "path.h"
#include "utility.h"
#include "texture.h"

GLuint mysphereID;

Protagonist::Protagonist(){
    GLUquadricObj *sphere=NULL;
    sphere = gluNewQuadric();
    gluQuadricDrawStyle(sphere, GLU_FILL);
    gluQuadricTexture(sphere, true);
    gluQuadricNormals(sphere, GLU_SMOOTH);
    //Making a display list
    mysphereID = glGenLists(1);
    glNewList(mysphereID, GL_COMPILE);
    gluSphere(sphere, 0.25, 15, 15);
    glEndList();
    gluDeleteQuadric(sphere);
    
    orien.z = 360; orien.x = 360;

    color_state = ColorRule::RED;
}

Protagonist::~Protagonist(){
    current = NULL;
}

//TODO: test for null situation to avoid crush
void Protagonist::render(){
    
    glPushMatrix();
   
    Matrix m = current->get_transform();
    glMultMatrixf(m.begin());
    glTranslatef(anchor.x, anchor.y, anchor.z);
    glTranslatef(0, 0.125, 0);
    
    glRotatef(orien.x, 1, 0, 0);
    glRotatef(orien.z, 0 ,0, 1);
    
    glColor3f(c.r , c.g , c.b);
    glCallList(mysphereID);

    glPopMatrix();
}

//rotate , not important for now
//    Vector z_cor = m * Vector(0,0,1);
//
//    glBegin(GL_LINES);
//    glColor3f(1, 0, 0);glVertex3f(0, 0, 0); glVertex3f(0, 0, 1);
//    glColor3f(0, 0, 1);glVertex3f(0, 0, 0); glVertex3f(z_cor.x, z_cor.y, z_cor.z); //same? not sure
//    glEnd();
//the distance from center to bottom
//    glBindTexture(GL_TEXTURE_2D, Texture::Instance().get_texture(Texture::MARBLE));
//    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
//    glBindTexture(GL_TEXTURE_2D, NULL);

void Protagonist::update(SDL_Event event){
    float speed = 0.2f;
    
    if (event.type == SDL_KEYDOWN) {
        SDLKey key_press = event.key.keysym.sym;
        if(key_press == SDLK_UP){

            Point next_anchor = anchor + Vector(1,0,0) * speed;
            orien.z -= 10; if (orien.z <= 0) orien.z = 360;
            
            if (current->is_on_surface(next_anchor)) { //if within
                anchor = next_anchor;
            }else if (current->next && current->next->is_path_color_valid()) { //&& next_anchor.is_within_dis(current->get_end(), speed)
                current->is_ball_on = false;
                current = current->next;
                anchor = Point();
                current->is_ball_on = true;
                
            }
        }else if(key_press == SDLK_DOWN){
           
            Point prev_anchor =  anchor + Vector(1,0,0) * -speed;
            orien.z += 10; if (orien.z >= 360) orien.z = 0;
            
            if (current->is_on_surface(prev_anchor)) { //this one can use the one before transform...
                anchor = prev_anchor;
            }else if (current->prev && current->prev->is_path_color_valid()){ 
                current->is_ball_on = false;
                current = current->prev;
                anchor = current->get_length_point();
                current->is_ball_on = true;
            }
        }
//        else if(key_press == SDLK_c){
//            if (color_state == ColorRule::RED) {
//                color_state = ColorRule::BLUE;
//                c = Color(0, 0, 1);
//            }else{
//                color_state = ColorRule::RED;
//                c = Color(1, 0, 0);
//            }
//            ColorRule::Instance().set_global_state(color_state);
//        }
    }
    
    //
    Vector new_eye_dis = current->get_transform() * Camera::Instance().get_eye_to_center();
    Camera::Instance().anime_camera(current->get_normal(), new_eye_dis);
    Camera::Instance().center = current->get_transform() * anchor;
}

//        else if(key_press == SDLK_LEFT){ //need to get z size
//            Point left_anchor = anchor + Vector(0,0,1) * -speed;
//            orien.x -= 10; if (orien.x <= 0) orien.x = 360;
//
//            if (current->is_on_surface(left_anchor)) anchor = left_anchor;
//
//        }else if(key_press == SDLK_RIGHT){
//            Point right_anchor = anchor + Vector(0,0,1) * speed;
//            orien.x += 10; if (orien.x >= 360) orien.x = 0;
//            if (current->is_on_surface(right_anchor)) anchor = right_anchor;
//
//        }
