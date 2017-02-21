//
//  Compound.cpp
//  Chemistry
//
//  Created by Jose Bouza on 3/26/16.
//  Copyright © 2016 Jose Bouza. All rights reserved.
//

#include "Compound.hpp"



void Compound::initialize(Node<std::vector<element_count>>* comp_raw)
{
    Compound::compound_structured = comp_raw;
    
    //Get unstructured data:
    Compound::compound_unstructured = getUnstructured(comp_raw);
}

Compound::Compound(std::string input, unsigned int comp_num)
{
    try{ initialize(parseCompound(input)); }
    catch(const std::invalid_argument& e) { throw e; }
    
    Compound::comp_id = comp_num;
    Compound::comp_str = input;
}

Compound::Compound(std::string input)
{
    try{ initialize(parseCompound(input)); }
    catch(const std::invalid_argument& e) { throw e; }
    
    Compound::comp_str = input;
}

Compound::Compound(Node<std::vector<element_count>>* comp_raw, unsigned int comp_id)
{
    initialize(comp_raw);
    Compound::comp_id = comp_id;
}

Compound::Compound(Node<std::vector<element_count>>* comp_raw)
{
    initialize(comp_raw);
}

Compound::Compound(std::vector<element_count> compound_unstructured)
{
    Compound::compound_unstructured = mergeData(compound_unstructured);
    Compound::compound_structured = NULL;
    
    std::string compound_str = "";
    
    for (element_count elem : compound_unstructured)
    {
        compound_str.append(elem.element.symbol());
        if(elem.count > 1)
            compound_str.append(std::to_string(elem.count));
    }
    
    Compound::comp_str = compound_str;
}

Compound::Compound(const Compound& other)
{
    this->compound_unstructured = other.compound_unstructured;
    this->comp_str = other.comp_str;
    this->comp_id = other.comp_id;
    
    //Node structure copy:
    this->compound_structured = new Node<std::vector<element_count>>(*other.compound_structured);
}

Compound::Compound()
{
    
}

Compound::~Compound()
{
    if( compound_structured != NULL && compound_structured->containsData() == true )
    {
        delete compound_structured;
    }
}

Compound::iterator Compound::begin()
{ return Compound::compound_unstructured.begin(); }


Compound::iterator Compound::end()
{ return Compound::compound_unstructured.end(); }


std::string Compound::compoundString() const
{
    return Compound::comp_str;
}

std::vector<element_count> Compound::getCompoundUnstructured()
{
    return Compound::compound_unstructured;
}


bool Compound::nodeEqualityDescent(Node<std::vector<element_count>>* node_1, Node<std::vector<element_count>>* node_2)
{
    int child_count_1 = node_1->getKeyBuffer();
    int child_count_2 = node_2->getKeyBuffer();
    
    Node<std::vector<element_count>>* node_1c = new Node<std::vector<element_count>>( *node_1 );
    Node<std::vector<element_count>>* node_2c = new Node<std::vector<element_count>>( *node_2 );
    
    
    std::vector<element_count> empty_vector;
    
    if( child_count_1 == child_count_2 )
    {
        //True by default.
        bool child_equal = true;
        
        if(child_count_1 > 0)
        {
            std::vector<Node<std::vector<element_count>>> child_list_1 = node_1c->generateChildList();
            std::vector<Node<std::vector<element_count>>> child_list_2 = node_2c->generateChildList();
        
            for( int i = 0; i < child_list_1.size(); i++)
            {
                bool child_found = false;
                for( int m = 0; m < child_list_2.size() && child_found == false; m++)
                {
                    if(nodeEqualityDescent(&child_list_1[i], &child_list_2[m]))
                    {
                        child_found = true;
                        
                        //We matched this child so we clear its contents to avoid matching again.
                        child_list_2[i].setData(empty_vector);
                        child_list_2[i].delete_node();
                    }
                }
                
                if(child_found == false)
                {
                    child_equal = false;
                    break;
                }
            }
        }
        
        //If two nodes are empty, we do not consider them equivilant. This is a hack that allows the
        //structure checker above to remove child nodes that it already paired.
        
        std::vector<element_count> node_1_data = node_1c->get();
        std::vector<element_count> node_2_data = node_2c->get();
        
        std::sort(node_1_data.begin(), node_1_data.end(), compareElementCount);
        std::sort(node_2_data.begin(), node_2_data.end(), compareElementCount);
        
        if( (node_1_data == node_2_data) && (node_1_data != empty_vector) && child_equal )
        {
            delete node_1c;
            delete node_2c;
            return true;
        }
        
        else
        {
            delete node_1c;
            delete node_2c;
            return false;
        }
        
    }
    
    
    else
    {
        delete node_1c;
        delete node_2c;
        return false;
    }
}


bool Compound::operator==(const Compound& comp)
{
    if( nodeEqualityDescent(this->compound_structured, comp.compound_structured) && this->getCompID() == comp.getCompID())
    {
        return true;
    }
    
    else
    {
        return false;
    }
}

unsigned int Compound::getCompID() const
{
    return Compound::comp_id;
}

//We define sorting to satisfy strict weak ordering for the map class.
bool Compound::operator<(const Compound& comp) const
{
    return comp.comp_id > this->comp_id;
}


double Compound::molar_mass_total()
{
    
    //Adds all the molar masses from a molar_mass_element() function to get total.
    std::map<ElementBase, double> molar_mass_list = Compound::molar_mass_element();
    double molar_mass_buffer = 0;
    
    for(element_count elem : compound_unstructured)
        molar_mass_buffer += molar_mass_list[elem.element];
    
    
    return molar_mass_buffer;
}


std::map<ElementBase, double> Compound::molar_mass_element()
{
    //maps each element to its molar mass by quantity in the compound.
    std::map<ElementBase, double> molar_masses;
    
    for(element_count elem : Compound::compound_unstructured)
        molar_masses[elem.element] = (elem.element.molarmass())*elem.count;
    
    
    return molar_masses;
    
}


std::map<ElementBase, double> Compound::mass_percent_element()
{
    //Finds ratio of each elements mass to the total mass
    double total_mass = Compound::molar_mass_total();
    std::map<ElementBase, double> molar_mass_list = Compound::molar_mass_element();
    std::map<ElementBase, double> molar_mass_ratio;
    
    
    
    for(element_count elem : Compound::compound_unstructured)
        molar_mass_ratio[elem.element] = (molar_mass_list[elem.element])/total_mass;
    
    
    return molar_mass_ratio;
}

Compound Compound::getEmpiricalCompound()
{
    //Get greatest count
    std::vector<element_count> comps = this->getCompoundUnstructured();
    
    if(!comps.empty())
    {
        element_count greatest_comp = comps[0];
        
        for(std::vector<element_count>::iterator it = comps.begin(); it != comps.end(); it++)
            if(it->count > greatest_comp.count)
                greatest_comp = *it;
        
        //Find gcf
        int gcf = 0;
        
        for( int i = 1; i < greatest_comp.count; i++ )
        {
            bool divides_all = true;
            
            for( std::vector<element_count>::iterator it = comps.begin(); it != comps.end(); it++)
            {
                if( it->count % i  != 0 )
                {
                    divides_all = false;
                }
            }
            
            if (divides_all && i > gcf)
            {
                gcf = i;
            }
        }
        
        if(gcf != 0)
        {
            for (element_count& elem : comps )
            {
                elem.count = elem.count/gcf;
            }
        }
    }
    
    return Compound(comps);
}



