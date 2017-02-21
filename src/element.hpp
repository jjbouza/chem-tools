//
//  element.hpp
//  Chemistry
//
//  Created by Jose Bouza on 2/20/16.
//  Copyright © 2016 Jose Bouza. All rights reserved.
//

#ifndef element_hpp
#define element_hpp

#include <string>


class ElementBase
{
public:
    void init(std::string symbol_in, double molar_mass_in, int iden_in)
    {molar_mass = molar_mass_in; symb = symbol_in; iden = iden_in;}
    
    double molarmass() const {return molar_mass;}
    std::string symbol() const {return symb;}
    int identifier() const {return iden;}
    
    bool operator ==(const ElementBase& other) const
    {
        return (iden == other.iden);
    }
    
    bool operator <(const ElementBase& other) const
    {
        return iden < other.iden;
    }
    
    bool operator >(const ElementBase& other) const
    {
        return iden > other.iden;
    }
    
private:
    double molar_mass;
    std::string symb;
    int iden;
};

//Wraps an element with a count
struct element_count
{
    ElementBase element;
    int count;
    
    //Comparison operator for element_count.
    bool operator==(const element_count& other) const
    {
        return (element == other.element)&&(count == other.count);
    }
};


#endif /* element_hpp */
