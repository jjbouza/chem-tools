//
//  parser.hpp
//  Chemistry
//
//  Created by Jose Bouza on 2/20/16.
//  Copyright © 2016 Jose Bouza. All rights reserved.
//

#ifndef parser_hpp
#define parser_hpp

#include <vector>
#include <utility>
#include <stdexcept>
#include <algorithm>
#include <string>
#include <ctype.h>

#include "Node.hpp"
#include "element.hpp"
#include "ElementDatabase.hpp"


struct reaction_data
{
    std::vector<std::pair<unsigned int, std::string>> lhs;
    std::vector<std::pair<unsigned int, std::string>> rhs;
};

enum INPUT_TYE {REACTION, COMPOUND};


//Gives the input type
INPUT_TYE classifyInput(std::string input);
    
//Returns base node to compound tree structure.
Node<std::vector<element_count>>* parseCompound(std::string comp_in);
    
//Returns a reaction data instance.
reaction_data parseReactionToStrings(std::string reaction);

std::string formatCompound(std::string compound);


#endif /* parser_hpp */
