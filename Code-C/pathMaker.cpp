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

Path* PathMaker::make_path_from_file(std::string fileName){
    std::ifstream file(fileName.c_str());
    std::string line;
    Path * root = NULL;
    
    if (file.is_open()){
        while ( getline (file,line) ){
            //1st we need to check the tag
            std::vector<std::string> items  =  split(line, ' ');
            std::string tag = items[0];
            items.erase(items.begin());
            //erase it
            if (tag == "Path ") {
                //TODO: we should get to the end of root first
                root = Path::make_path_from_string(items);
            }else if(tag == "EndPath"){
                //TODO: get to the end
                
                //I think we should get all those function here, no need to make static one
            }else{
                //Do clean up of current path
                Path::delete_path(root);
                file.close();
                break;
            }
            
            //why don't we give back vectors directly?
        }
        file.close();
    }
    
    
    return root;
}