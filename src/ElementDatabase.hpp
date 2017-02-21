//
//  ElementDatabase.hpp
//  Chemistry
//
//  Created by Jose Bouza on 2/21/16.
//  Copyright © 2016 Jose Bouza. All rights reserved.
//

#ifndef ElementDatabase_hpp
#define ElementDatabase_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include <stdexcept>

#include "element.hpp"



class ElementDatabase
{
public:
    ElementDatabase(std::vector<ElementBase> data);
    ElementDatabase();
    
    ElementBase find(std::string element_sym);
    
private:
    std::vector<ElementBase> data;
};

#endif /* ElementDatabase_hpp */

