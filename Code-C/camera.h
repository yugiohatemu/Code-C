//
//  camera.h
//  Code-C
//
//  Created by Yue on 11/30/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#ifndef __Code_C__camera__
#define __Code_C__camera__

//singelton

#include "algebra.h"

class Camera{
public:
    enum{
        FRONT_VIEW,
        RIGHT_VIEW,
        BACK_VIEW,
        LEFT_VIEW,
        TOTAL_VIEW
    }CAMERA_VIEW; //view based on protagoinist?
    
    static Camera& Instance();
    void init_camera();
    void switch_view();
    
private:
    Camera();  // Private so that it can  not be called
    Camera(Camera const&);             // copy constructor is private
    Camera& operator=(Camera const&);
    
    Vector views[TOTAL_VIEW];
};

#endif /* defined(__Code_C__camera__) */
