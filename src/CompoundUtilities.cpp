//
//  CompoundUtilities.cpp
//  Chemistry
//
//  Created by Jose Bouza on 6/29/16.
//  Copyright © 2016 Jose Bouza. All rights reserved.
//

#include "CompoundUtilities.hpp"


//Gives count of a certain element in a compound. Returns 0 if compound does not contain element.
int getCount(std::vector<element_count> compound, ElementBase elem)
{
    std::vector<element_count> compound_unstructured = mergeData(compound);
    
    for(element_count elem_portion : compound_unstructured)
    {
        if(elem_portion.element == elem)
        {
            return elem_portion.count;
        }
    }
    
    return 0;
}

//Merges like elements in an element list
std::vector<element_count> mergeData(std::vector<element_count> compound_data)
{
    std::vector<element_count>  merged_data;
    
    
    for(element_count data_portion : compound_data)
    {
        bool found_repeat = false;
        
        for(element_count& merge_portion : merged_data)
        {
            if( merge_portion.element == data_portion.element )
            {
                found_repeat = true;
                merge_portion.count += data_portion.count;
                break;
            }
        }
        
        if(found_repeat == false)
        {
            merged_data.push_back(data_portion);
        }
        
       
    }
    
    return merged_data;
}

//Gives unstructured element list form of a Node compound
std::vector<element_count> getUnstructured(Node<std::vector<element_count>>* comp_raw)
{
    std::vector<element_count> comp_unstrucutured;
    
    if( comp_raw->containsData() )
    {
        std::vector<element_count> node_data = comp_raw->get();
        
        for( element_count data_portion : node_data )
        {
            comp_unstrucutured.push_back(data_portion);
            comp_unstrucutured.back().count *= comp_raw->getMultilier();
        }
    }
    
    
    int key_buffer = comp_raw->getKeyBuffer();
    if(key_buffer > 0)
    {
        for(int i = 0; i < key_buffer; i++)
        {
            std::vector<element_count> child_data = getUnstructured(comp_raw->branch(key_buffer));
            
            for( element_count data_portion : child_data)
            {
                data_portion.count *= comp_raw->getMultilier();
                comp_unstrucutured.push_back(data_portion);
            }
        }
    }
    
    std::vector<element_count> comp_unstrucutured_final = mergeData(comp_unstrucutured);
    
    return comp_unstrucutured_final;
}

bool compareElementCount(const element_count &a, const element_count &b)
{
    return a.element.identifier() < b.element.identifier();
}



