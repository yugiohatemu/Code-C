//
//  pathMaker.cpp
//  Code-C
//
//  Created by Yue on 12/24/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "pathMaker.h"
#include <fstream>
#include "flipPath.h"
#include "flipColorPath.h"
#include "flyPath.h"
#include "endPath.h"
#include "dyePath.h"
#include "spritePath.h"
#include "utility.h"
#include "levelScreen.h"
#include <stack>
//Simpleset
//Path (x,x,x) (x,x,x) (x,x,x)....
//EndPath (x,x,x)

Path* make_consecutive_path(Point trans, std::vector<Vector> trans_list, ColorRule::State color_state){
    
    Color color = ColorRule::Instance().get_color(color_state);
    Path * head = new Path(trans, trans_list[1], trans_list[2]);
    head->c = color; head->color_state = color_state;
    
    Path * prev = head;
    
    for (int i = 2; i < trans_list.size(); i += 2) {
        Point p =  prev->get_transform() * prev->get_end();
        //Instead of doing this, what about a new method like creat next path?
        //maybe
        Path * next = new Path(p, trans_list[i], trans_list[i+1]);
        next->c = color; next->color_state = color_state;
        
        Path::link_path(prev,next);
        prev = next;
        
    }
    
    return head;
}


Path* make_path_from_string(std::vector<std::string>& items, Point trans){
    ColorRule::State path_color;
    try {
        path_color = ColorRule::Instance().get_state_from_string(items[0]);
    } catch (std::exception & e) {
        debug(e.what());
        return NULL;
    }
    
    items.erase(items.begin());

    //Ok, so the problem is here, we need an
    //After the color, check for # first, should be 2n
    if (items.size() < 2 || items.size() %2 == 1) return NULL;
    
    std::vector<Vector> trans_list;
    for (int i = 0; i < items.size(); i++) {
        try {
            trans_list.push_back(Vector::get_vector_from_string(items[i]));
        } catch (std::exception &e) {
            debug(e.what());
            return NULL;
        }
    }
    
    return make_consecutive_path(trans, trans_list, path_color);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

EndPath* make_endpath_from_string(std::vector<std::string>& items, Point trans){
    
    if (items.size() != 1) return NULL;
    
    Vector rot;
    try {
        rot = Vector::get_vector_from_string(items[0]);
    } catch (std::exception & e) {
        debug(e.what());
        return NULL;
    }
    
    return new EndPath(trans,rot);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//color, (rotate)+
FlipPath* make_flippath_from_string(std::vector<std::string>& items, Point trans){
    ColorRule::State path_color;
    try {
        path_color = ColorRule::Instance().get_state_from_string(items[0]);
        items.erase(items.begin());
    } catch (std::exception & e) {
        debug(e.what());
        return NULL;
    }
    //After color, get rotate
    if (items.size() < 1) return NULL;
    
    //Now parse colors
    std::vector<Vector> rotate_list;
    for (int i = 0; i < items.size(); i++) {
        try {
            rotate_list.push_back(Vector::get_vector_from_string(items[i]));
        } catch (std::exception &e) {
            debug(e.what());
            return NULL;
        }
    }
    
    FlipPath * p =  new FlipPath(trans, rotate_list);
    p->color_state = path_color; p->c = ColorRule::Instance().get_color(path_color);
    return p;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//FlipColorPath, n, (color)^n , (orien)^n, rotate
FlipColorPath * make_flipcolorpath(std::vector<std::string>& items, Point trans){
    //maybe a # to indicate how much?, since we should avoid use try & catch
    if(items.size() < 6 || items.size() % 2 == 1) return NULL;
    //need at leats two color/match with two orien so 2n + 2, the least should be 6 elements
    int count = 0;
    try{
        count = get_int(items[0]);
    }catch(std::exception & e) {
        debug(e.what());
        return NULL;
    }
    if (count < 2) return NULL;
    
    //now based on count, get expected color and orien
    std::vector<ColorRule::State> next_color;
    for(int i = 1; i <= count ; i ++){
        try{
            next_color.push_back(ColorRule::Instance().get_state_from_string(items[i]));
        }catch(std::exception & e) {
            debug(e.what());
            return NULL;
        }
    }
    //get orien, eg,
    std::vector<float> next_orien;
    for(int i = 1; i <= count ; i ++){
        try{
            next_orien.push_back(get_int(items[count + i]));
        }catch(std::exception & e) {
            debug(e.what());
            return NULL;
        }
    }
    
    //now we have one vector left
    Vector rotate;
    try{
        rotate = Vector::get_vector_from_string(items[1 + 2 * count]);
    }catch(std::exception & e) {
        debug(e.what());
        return NULL;
    }
    
    //TODO: test things afterwards? or just ignore?
    
    return new FlipColorPath(trans, rotate, next_color, next_orien);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//DyePath

DyePath* make_dyepath(std::vector<std::string>& items, Point trans){
    //color， rotate , color(ball)
    if (items.size() > 3) return NULL;
    
    ColorRule::State path_color;
    try {
        path_color = ColorRule::Instance().get_state_from_string(items[0]);
    } catch (std::exception & e) {
        debug(e.what());
        return NULL;
    }
    
    Vector rot;
    try {
        rot = Vector::get_vector_from_string(items[1]);
    } catch (std::exception & e) {
        debug(e.what());
        return NULL;
    }

    //Dye info
    ColorRule::State dye_color;
    try {
        dye_color = ColorRule::Instance().get_state_from_string(items[2]);
    } catch (std::exception & e) {
        debug(e.what());
        return NULL;
    }
    
    DyePath * path = new DyePath(trans,rot,dye_color);
    path->color_state = path_color;
    path->c = ColorRule::Instance().get_color(path_color);
    
    return path;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Sprite Path

SpritePath * make_spritepath(std::vector<std::string>& items, Point trans){
    if (items.size() < 3) return NULL;
    ColorRule::State path_color;
    try {
        path_color = ColorRule::Instance().get_state_from_string(items[0]);
    } catch (std::exception & e) {
        debug(e.what());
        return NULL;
    }
    
    Vector rot;
    try {
        rot = Vector::get_vector_from_string(items[1]);
    } catch (std::exception & e) {
        debug(e.what());
        return NULL;
    }
    
    //WARNING:this is just cheating now
    SpritePath * path = new SpritePath(trans,rot);
    path->color_state = path_color;
    path->c = ColorRule::Instance().get_color(path_color);
    
    return path;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//check for tab count to determine heirarchy, assume 4 space tab
int get_tab_count(std::string s){
    int i = 0;
    while (s[i] == ' ') i += 1;
    i /= 4;
    return  i;
}


Path* PathMaker::make_path_from_file(std::string fileName, LevelScreen * level){
    std::ifstream file(fileName.c_str());
    std::string line;
    Path * root = NULL;
    
    std::stack<Path *> tab_tree;
    std::stack<Point> multi_end;
    //will things get delted once out of stack?
    if (file.is_open()){
        while ( getline (file,line) ){
            Path * next_path = NULL;
            Path * current_path = NULL;
            
            int tab = get_tab_count(line);
            
            if(tab > tab_tree.size() + 1){
                debug("Tab Heirarchy ERROR");
                //TODO: goto clean up
            }else{
                int dif = (int)tab_tree.size() - tab;
//                debug(dif);
                if (root) {
                    for (int i = 0; i < dif; i++) tab_tree.pop();
                    current_path = tab_tree.top();
                }
                //something like this, so we don't need to worry about heirarch too much
            }

            std::vector<std::string> items = split(line, ' ');
            //stripe the tag
            std::string tag = items[0]; items.erase(items.begin());
            
            //
            Path * end_of_root = Path::end_of_path(current_path);
            
            bool flip_flag = false;
            FlipPath * flip_root = dynamic_cast<FlipPath *>(end_of_root);
            Point end_point;
            
            if (flip_root) {
                flip_flag = true;
                end_point = multi_end.top(); multi_end.pop();
            }else if (end_of_root) {
                end_point = end_of_root->get_transform()* end_of_root->get_end();
            }
            
            
            if (tag == "Path") {
                
                if(!root) {
                    root = make_path_from_string(items, Point());
                    next_path = root;
                }else{
                    Path * end_path = make_path_from_string(items, end_point);
                    if(end_path){
                        if (flip_flag) flip_root->add_next_path(end_path);
                        else Path::link_path(end_of_root, end_path);
                    }
                    next_path = end_path;
                }
                
            }else if(tag == "EndPath"){
                EndPath * end_path = make_endpath_from_string(items, end_point);
                if(end_path){
                    end_path->screen = level;
                    if (flip_flag) flip_root->add_next_path(end_path);
                    else Path::link_path(end_of_root, end_path);
                }
                next_path = end_path;
                
            }else if(tag == "FlipPath"){
                FlipPath * flip_path = make_flippath_from_string(items,end_point);
                if (flip_path) {
                    if (flip_flag) flip_root->add_next_path(flip_path);
                    else Path::link_path(end_of_root, flip_path);
                    
                    std::vector<Point> points = flip_path->get_end_point_list();
                    for (Point & p : points) multi_end.push(p);
                    
                }
                next_path = flip_path;
            
            }else if(tag == "FlipColorPath"){
                FlipColorPath * flipcolor_path = make_flipcolorpath(items, end_point);
                if(flipcolor_path){
                    if (flip_flag) flip_root->add_next_path(flipcolor_path);
                    else Path::link_path(end_of_root, flipcolor_path);
                }
                next_path = flipcolor_path;

            }else if (tag == "DyePath"){
                DyePath * dye_path = make_dyepath(items, end_point);
                if(dye_path){
                    if (flip_flag) flip_root->add_next_path(dye_path);
                    else Path::link_path(end_of_root, dye_path);
                }
                next_path = dye_path;
            }else if (tag == "SpritePath"){
                SpritePath * sprite_path = make_spritepath(items, end_point);
                if (sprite_path) {
                    if (flip_flag) flip_root->add_next_path(sprite_path);
                    else Path::link_path(end_of_root, sprite_path);
                }
                next_path = sprite_path;
            }
            
            //Check if we can proceed to process next path
            if (next_path == NULL) {
                Path::delete_path(root);
                root = NULL;
                break;
            }else{
                tab_tree.push(next_path);
            }
            
        }
        file.close();
    }
    if (!multi_end.empty()) {
        debug("Missing path hierarchy");
    }
    
    return root;
}