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
#include "utility.h"
#include "levelScreen.h"
#include <stack>
//Simpleset
//Path (x,x,x) (x,x,x) (x,x,x)....
//EndPath (x,x,x)

Path* make_consecutive_path(Point trans, std::vector<Vector> trans_list, ColorRule::State color_state){
    
    Color color = ColorRule::Instance().get_color(color_state);
    Path * head = new Path(trans, trans_list[1], trans_list[2]); head->c = color;
    
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
    
    return new FlipPath(trans, rotate_list);
}

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
                for (int i = 0; i < dif; i++) tab_tree.pop();
                current_path = tab_tree.top();
                //something like this, so we don't need to worry about heirarch too much
            }

            std::vector<std::string> items = split(line, ' ');
            std::string tag = items[0]; items.erase(items.begin());
            Path * end_of_root = Path::end_of_path(current_path);
            Point end_point = end_of_root->get_transform()* end_of_root->get_end();
            //TODO: cast to flipPoint? if so ,we need to use add_link instead of Path::link, we can use a flag to do that
            //and adjust flipPath
            //Now it is getting cleaner and bearable
            
            if (tag == "Path") {
                
                if(!root) {
                    root = make_path_from_string(items, Point());
                    if (!root) break;
                }else{
                    Path * end_path = make_path_from_string(items, end_point);
                    next_path = end_path;
                    
                    if(end_path){
                        Path::link_path(end_of_root, end_path);
                    }
                }
                
            }else if(tag == "EndPath"){
                //Get the actual end from vector
                EndPath * end_path = make_endpath_from_string(items, end_point);
                next_path = end_path;
                if(end_path){
                    end_path->screen = level;
                    Path::link_path(end_of_root, end_path);
                }
                
            }else if(tag == "FlipPath"){
                FlipPath * flip_path = make_flippath_from_string(items,end_point);
                if (flip_path) {
                    Path::link_path(end_of_root, flip_path);
                    std::vector<Point> points = flip_path->get_end_point_list();
                    for (Point & p : points) multi_end.push(p);
                    
                }
                next_path = flip_path;
            
            }
            
            if (next_path == NULL) {
                Path::delete_path(root);
                break;
            }else{
                tab_tree.push(next_path);
            }
            
        }
        file.close();
    }
    
    
    return root;
}