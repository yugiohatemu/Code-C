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

//Simpleset
//Path (x,x,x) (x,x,x) (x,x,x)....
//EndPath (x,x,x)

Path* make_consecutive_path( std::vector<Vector> trans_list, Color color){
    if (trans_list.size() < 2 || trans_list.size() % 2 != 0) return NULL;
    //Lets always assume we start from 0, so save us from troubles 
    Path * head = new Path(Point(), trans_list[1], trans_list[2]); head->c = color;
    
    if (color == Color(1, 0, 0)) {
        head->color_state = ColorRule::RED;
    }else if (color == Color(0, 0, 1)){
        head->color_state = ColorRule::BLUE;
    }
    
    Path * prev = head;
    
    for (int i = 3; i < trans_list.size(); i += 2) {
        Point p =  prev->get_transform() * prev->get_end();
        
        //so translate to start first, rotate, then translate back?
        Path * next = new Path(p, trans_list[i], trans_list[i+1]); next->c = color;
        if (color == Color(1, 0, 0)) {
            next->color_state = ColorRule::RED;
        }else if (color == Color(0, 0, 1)){
            next->color_state = ColorRule::BLUE;
        }
        
        Path::link_path(prev,next);
        prev = next;
        
    }
    
    return head;
}


Path* make_path_from_string(std::vector<std::string>& items){
    ColorRule::State path_color;
    try {
        path_color = ColorRule::Instance().get_state_from_string(items[0]);
    } catch (std::exception & e) {
        debug(e.what());
        return NULL;
    }
    
    items.erase(items.begin());
    
    //After the color, check for # first, should be 3 + 2n
    if (items.size() < 3 || items.size() %2 == 0) return NULL;
    
    std::vector<Vector> trans_list;
    for (int i = 1; i < items.size(); i++) {
        try {
            trans_list.push_back(Vector::get_vector_from_string(items[i]));
        } catch (std::exception &e) {
            debug(e.what());
            return NULL;
        }
    }
    return make_consecutive_path(trans_list, path_color);
}


EndPath* make_end_path_from_string(std::vector<std::string>& items, Point trans){
    
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


Path* PathMaker::make_path_from_file(std::string fileName){
    std::ifstream file(fileName.c_str());
    std::string line;
    Path * root = NULL;
    Path * end_of_root = NULL;
    if (file.is_open()){
        while ( getline (file,line) ){
            //1st we need to check the tag
            std::vector<std::string> items = split(line, ' ');
            std::string tag = items[0];
            items.erase(items.begin());
            //2nd one should always be color
            //erase it
            if (tag == "Path ") {
                //TODO: we should get to the end of root first
                if(!root) {
                    root = make_path_from_string(items);
                }
                else{
                    end_of_root = Path::end_of_path(root);
                    Point end = end_of_root->get_transform()* end_of_root->get_end();
                    Path * end_path = make_path_from_string(items);
                    //TODO: need to change how we handle path parsing
                    if(end_path){
                        Path::link_path(end_of_root, end_path);
                    }else{
                        Path::delete_path(root);
                        break;
                    }
                }
                //After that
                if (!root) break;
            }else if(tag == "EndPath"){
                
                end_of_root = Path::end_of_path(root);
                Point end = end_of_root->get_transform()* end_of_root->get_end();
                //Get the actual end from vector
                EndPath * end_path = make_end_path_from_string(items, end);
                if(end_path){
                    Path::link_path(end_of_root, end_path);
                }else{
                    Path::delete_path(root);
                    break;
                }
            }else{
                //Do clean up of current path
                Path::delete_path(root);
                break;
            }
            
        }
        file.close();
    }
    
    
    return root;
}