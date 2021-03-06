//
//  main.cpp
//  Code-C
//
//  Created by Yue on 11/28/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//


#include <GLUT/GLUT.h>
#include <OpenGL/gl.h>
#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"

///////////////////////////////////////////////////////////////////
//Several things changed in build setting
//Build search path
//Deployment target is changed to OSX 10.8 to surpress warning for glut
//ARC is disabled to allow compilation of SDLMain
///////////////////////////////////////////////////////////////////

#include "stopWatch.h"
#include "texture.h"
#include "screenController.h"
#include "levelScreen.h"
#include "levelSelectScreen.h"
#include "shapeBuilder.h"

//Screen attributes
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;


bool initGL(){
    //Initialize Projection Matrix
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40, 1, 1.0, 100.0);
    
    glMatrixMode(GL_MODELVIEW);
    gluLookAt(0.0, 5.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    //5 ,10,/ -5, 10 / -5, -10 / 5 - 10
    //Initialize clear color
    glClearColor( 1.f, 1.f, 1.f, 1.f );
    
    //Check for error
    GLenum error = glGetError();
    if( error != GL_NO_ERROR ){
        printf( "Error initializing OpenGL! %s\n", gluErrorString( error ) );
        return false;
    }
    
    //Clear color buffer
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //clear color and depth
    glEnable(GL_COLOR_MATERIAL);
    //enable texture
    glEnable( GL_TEXTURE_2D );
    glEnable(GL_DEPTH_TEST);
    //enable lines
    glEnable(GL_LINE_SMOOTH);
    //
    glShadeModel(GL_SMOOTH);
    //
    GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 1.0};  /* Red diffuse light. */
    GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0};  /* Infinite light location. */
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    
    
    return true;
}



bool init(){
    //Initialize SDL
    if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 ) return false;
    
    //Create Window
    if( SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_OPENGL ) == NULL ) return false;
    
    //Enable unicode
    SDL_EnableUNICODE( SDL_TRUE );
    
    //Initialize OpenGL
    if( !initGL()) return false;
    
    //Set caption
    SDL_WM_SetCaption( "Code-C", NULL );
    
    return true;
}

int main( int argc, char *argv[] ){
    //Quit flag
    bool quit = false;
    
    //Initialize
    if( init() == false ) return 1;
    
    //The frame rate regulator
    StopWatch fps(0.1);
    fps.start();
    
    Texture::Instance().load_file("/Users/wei/Desktop/Code-C/Code-C/marble.png", 256, 256);
    ShapeBuilder::Instance().init();
    SDL_Event event;
    
    ScreenController * root_controller = new ScreenController(new LevelSelectScreen());
    
	while( !quit ){
        
		while( SDL_PollEvent( &event ) ){
			if( event.type == SDL_QUIT )quit = true;
            if (event.type == SDL_KEYDOWN) {
                if(event.key.keysym.sym == SDLK_ESCAPE) quit = true;
            }
		}
        
        if (fps.is_timeup()){
            
            root_controller->render();
            root_controller->update(event);
            SDL_GL_SwapBuffers();
            fps.start();
        }
	}
    

    Texture::Instance().clean_texture();
    ShapeBuilder::Instance().clear();
    delete root_controller;
    
	//Clean up
	SDL_Quit();
	return 0;
}



