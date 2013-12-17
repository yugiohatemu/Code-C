//
//  colorRule.h
//  Code-C
//
//  Created by Yue on 12/16/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#ifndef __Code_C__colorRule__
#define __Code_C__colorRule__

#include "color.h"

class ColorRule{
public:
    static ColorRule& Instance();
    enum State{
        BLACK,
        WHITE,
        BLUE,
        RED,
        TOTAL_STATE
    };
    State global_state;
    bool is_state_global(State state);
    void set_global_state(State state);
private:
    Color get_color(State state);
    ColorRule();
    ColorRule(ColorRule const &);
    ColorRule& operator= (ColorRule const &);
     //if the state is visible/interactable, return yes

};

#endif /* defined(__Code_C__colorRule__) */
