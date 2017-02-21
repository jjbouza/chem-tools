//
//  CompoundUtilities.hpp
//  Chemistry
//
//  Created by Jose Bouza on 6/29/16.
//  Copyright © 2016 Jose Bouza. All rights reserved.
//

#ifndef CompoundUtilities_hpp
#define CompoundUtilities_hpp

#include <vector>
#include <cmath>

#include "parser.hpp"


//Gives count of a certain element in a compound. Returns 0 if compound does not contain element.
int getCount(std::vector<element_count> compound, ElementBase* elem);

//Merges like elements in an element list
std::vector<element_count> mergeData(std::vector<element_count> compound_data);

//Gives unstructured element list form of a Node compound
std::vector<element_count> getUnstructured(Node<std::vector<element_count>>* comp_raw);

//Used to sort element_count vectors by counts:
bool compareElementCount(const element_count &a, const element_count &b);


#endif /* CompoundUtilities_hpp */
