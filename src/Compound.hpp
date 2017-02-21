//
//  Compound.hpp
//  Chemistry
//
//  Created by Jose Bouza on 3/26/16.
//  Copyright © 2016 Jose Bouza. All rights reserved.
//

#ifndef Compound_hpp
#define Compound_hpp

#include <string>
#include <vector>
#include <map>

#include "Node.hpp"
#include "parser.hpp"
#include "CompoundUtilities.hpp"

class Compound
{
private:
    //Every compound must have a comp_id
    unsigned int comp_id;
    
    //Base class initializer
    void initialize(Node<std::vector<element_count>>* comp_raw);
    
    //Node structure of compound
    Node<std::vector<element_count>>* compound_structured;
    
    
    //Checks that two compounds are structurally equivilant.
    bool nodeEqualityDescent(Node<std::vector<element_count>>* node_1, Node<std::vector<element_count>>* node_2);
    
    //List of elements in compound
    typedef std::vector<element_count> compound_list;
    compound_list compound_unstructured;
    std::string comp_str;
    
    
public:
    //For use by reaction constructor
    Compound(std::string input, unsigned int comp_id);
    Compound(std::string input);

    Compound(Node<std::vector<element_count>>* comp_raw, unsigned int comp_id);
    Compound(Node<std::vector<element_count>>* comp_raw);

    //Structure-less compound:
    Compound(std::vector<element_count> compound_unstructured);
    //Copy constructor: Handles reassigment of compound_structured
    Compound(const Compound& other);
    //Empty constructor
    Compound();
    ~Compound();
    
    //Define iterator over compound_list. This iterates over the unstructured compound.
    typedef compound_list::iterator iterator;
    typedef compound_list::const_iterator const_iterator;
    
    iterator begin();
    iterator end();
    
    unsigned int getCompID() const;
    
    //Defines equality operator for compounds. Checks that Node strucutre is same. 
    bool operator==(const Compound& comp);
    
    bool operator<(const Compound& comp) const;
    
    double molar_mass_total();
    std::map<ElementBase, double> molar_mass_element();
    std::map<ElementBase, double> mass_percent_element();
    
    std::string compoundString() const;
    
    std::vector<element_count> getCompoundUnstructured();
    
    Compound getEmpiricalCompound();
    
};

#endif /* Compound_hpp */
