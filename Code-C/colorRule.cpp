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

ColorRule::State ColorRule::get_state_from_string(std::string s) throw (std::exception){
    if (s == "BLACK") return BLACK;
    else if( s== "RED") return RED;
    else if( s == "BLUE") return BLUE;
    else if( s == "WHITE") return WHITE;
    else throw ParseError("C:Invalid Color");
    
    return TOTAL_STATE;
}

Color ColorRule::get_color(State state){
    if (state == BLUE) return Color(0,0,1);
    else if(state == RED) return Color(1,0,0);
    else if(state == BLACK) return Color(0,0,0);
    else if(state == WHITE) return Color(1,1,1);
    return Color();
}
