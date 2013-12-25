//
//  colorRule.cpp
//  Code-C
//
//  Created by Yue on 12/16/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "colorRule.h"

ColorRule::ColorRule(){}

ColorRule::ColorRule(ColorRule const &){}

ColorRule& ColorRule::operator= (ColorRule const &){
    return *this;
}

ColorRule& ColorRule::Instance(){
    static ColorRule m_Instance;
    return m_Instance;
}

////////////////////////////////////////////////////////////////////////////////

bool ColorRule::is_state_global(State state){
    return state == BLACK || state == WHITE ||state == global_state;
}

void ColorRule::set_global_state(State state){
    global_state = state;
}

ColorRule::State ColorRule::get_state_from_string(std::string s){
    if (s == "BLACK") return BLACK;
    else if( s== "RED") return RED;
    else if( s == "BLUE") return BLUE;
    else if( s == "WHITE") return WHITE;
    
    return ERROR;
}