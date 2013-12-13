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
    gluSphere(sphere, 0.5, 15, 15);
    glEndList();
    gluDeleteQuadric(sphere);
    
    orien.z = 360;

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
    glTranslatef(0, 0.25, 0);
    //rotate , not important for now
//    Vector z_cor = m * Vector(0,0,1);
//    
//    glBegin(GL_LINES);
//    glColor3f(1, 0, 0);glVertex3f(0, 0, 0); glVertex3f(0, 0, 1);
//    glColor3f(0, 0, 1);glVertex3f(0, 0, 0); glVertex3f(z_cor.x, z_cor.y, z_cor.z); //same? not sure
//    glEnd();
    
    
    glRotatef(orien.z, 0 , 0, 1);
    //the distance from center to bottom
    glBindTexture(GL_TEXTURE_2D, Texture::Instance().get_texture(Texture::MARBLE));
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glCallList(mysphereID);
    glBindTexture(GL_TEXTURE_2D, NULL);

    glPopMatrix();
}


void Protagonist::update(SDL_Event event){
    float speed = 0.1f;
    
    if (event.type == SDL_KEYDOWN) {
        SDLKey key_press = event.key.keysym.sym;
        if(key_press == SDLK_UP){

            Point next_anchor = current->get_transform() * (anchor + Vector(1,0,0) * speed);
            orien.z -= 5; if (orien.z <= 0) orien.z = 360;
            //Problem, we need to use the surface normal to do that?
            
            if (next_anchor.is_whithin(current->get_start(), current->get_end())) { //if within
                anchor = anchor+ Vector(1,0,0) * speed;
                Camera::Instance().center = next_anchor;
            }else{
                //reset anchor to avoid over multiply translation
                if (current->next) {
                    current = current->next;
                    anchor = Point();
                    
                    Camera::Instance().center = current->get_start();
//                    Camera::Instance().up = current->get_normal();
                    Camera::Instance().anime_camera(current->get_normal());
                }
            }
        }else if(key_press == SDLK_DOWN){
           
            Point prev_anchor = current->get_transform() * ( anchor + Vector(1,0,0) * -speed);
            orien.z += 5; if (orien.z >= 360) orien.z = 0;
            
            if (prev_anchor.is_whithin(current->get_start(), current->get_end())) { //if within
                anchor = anchor + Vector(1,0,0) * -speed;
                Camera::Instance().center = prev_anchor;
            }else{
                //reset anchor point
                if (current->prev) {
                    //one way is to get ,or say scale, because invert is inaccurate
                    current = current->prev;
                    anchor = current->get_length_point();
                    
                    Camera::Instance().center = current->get_end();
//                    Camera::Instance().up = current->get_normal();
                    Camera::Instance().anime_camera(current->get_normal());
                }
            }
        }else if(key_press == SDLK_LEFT){
        
        }else if(key_press == SDLK_RIGHT){
            
        }
    }
}


