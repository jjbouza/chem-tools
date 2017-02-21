//
//  parser.cpp
//  Chemistry
//
//  Created by Jose Bouza on 2/20/16.
//  Copyright © 2016 Jose Bouza. All rights reserved.
//

#include "parser.hpp"

INPUT_TYE classifyInput(std::string input)
{
    if(input.find('+') != std::string::npos)
        return REACTION;
    
    else
        return COMPOUND;
}

std::string formatCompound(std::string comp_in)
{
    
    try { parseCompound(comp_in); }
    catch( const std::invalid_argument& e)
    {
        try { parseReactionToStrings(comp_in); }
        catch (const std::invalid_argument& e)
        {
            if(comp_in.find("+") == std::string::npos && (comp_in.find("(") == std::string::npos))
            {
                std::transform(comp_in.begin(), comp_in.end(), comp_in.begin(), ::tolower);
            }
            
            return comp_in;
        }

    }
    
    ElementDatabase elems;
    
    for(int i = 0; i < comp_in.size(); i++)
    {
        if(isalpha(comp_in[i]))
        {
            if(islower(comp_in[i]))
            {
                bool first_char_is_element = true;
                bool first_and_second_char_is_element = true;
                
                //See if capitalized element is an element.
                try { elems.find(std::string(1, std::toupper(comp_in[i]))); }
                catch(const std::invalid_argument& e)
                { first_char_is_element = false; }
                
                //See if the user meant to write a two character element.
                std::string temp_str = std::string(1,std::toupper(comp_in[i]));
                temp_str += comp_in[i+1];
                try { elems.find(temp_str); }
                catch(const std::invalid_argument& e2)
                { first_and_second_char_is_element = false; }
                
                
                if(first_and_second_char_is_element == false && first_char_is_element == true)
                    comp_in[i] = toupper(comp_in[i]);
                    
                else if(first_char_is_element == false && first_and_second_char_is_element == true)
                {
                    comp_in[i] = toupper(comp_in[i]);
                    i++;
                }
                
                //We assume that co2 = CO2
                else if(first_char_is_element == true && first_and_second_char_is_element == true)
                {
                    comp_in[i] = toupper(comp_in[i]);
                    i++;
                }
                    
                else if(first_and_second_char_is_element == false && first_char_is_element == false)
                {
                    throw std::invalid_argument("Element symbol could not be interpreted from input: " + comp_in);
                }
            }
            
            else if(isupper(comp_in[i]))
            {
                if(islower(comp_in[i+1]))
                {
                    std::string string_buffer = "";
                    string_buffer += comp_in[i];
                    string_buffer += comp_in[i+1];
                    
                    try { elems.find(string_buffer); }
                    catch(const std::invalid_argument &e)
                    {
                        throw std::invalid_argument("Invalid element symbols:" + std::string(2, (comp_in[i] + comp_in[i+1])));
                    }
                    
                    i++;
                }
                
                else
                {
                    try { elems.find(std::string(1, comp_in[i])); }
                    catch(const std::invalid_argument &e)
                    {
                        throw std::invalid_argument("Invalid element symbol:" + std::string(1, (comp_in[i])));
                    }
                    
                }
                
            }
            
        }
    }
    
    return comp_in;
}


//Recursive parsing algorithm.
Node<std::vector<element_count>>* parseCompound(std::string comp_in)
{
    ElementDatabase elems;
    
    //Node is allocated on heap as the multiplier tree implementation requests.
    Node<std::vector<element_count>>* cur_node = new Node<std::vector<element_count>>(1);
    //Used to store temporary strings that must be global to the function.
    std::string string_buffer;
    //Temporarly holds the data for the node.
    std::vector<element_count> compound_data;
    

    
    for(int i = 0; i < comp_in.size(); i++)
    {
        //Character signifies possible element. We find the element in database and store temporarily in compound_data.
        if(isalpha(comp_in[i]))
        {
            element_count elem;
            
            //This may be ambiguous since we allow lowercase characters.
            //We try to derive the meaning or give a guess of what the user met. For example: is co2 = CO2 or Co2?
            if(islower(comp_in[i]))
            {
                bool first_char_is_element = true;
                bool first_and_second_char_is_element = true;
                
                //See if capitalized element is an element.
                try { elems.find(std::string(1, std::toupper(comp_in[i]))); }
                catch(const std::invalid_argument& e)
                { first_char_is_element = false; }
                
                //See if the user meant to write a two character element.
                std::string temp_str = std::string(1,std::toupper(comp_in[i]));
                temp_str += comp_in[i+1];
                try { elems.find(temp_str); }
                catch(const std::invalid_argument& e2)
                { first_and_second_char_is_element = false; }
                
                
                if(first_and_second_char_is_element == false && first_char_is_element == true)
                    elem.element = elems.find(std::string(1, std::toupper(comp_in[i])));
                
                else if(first_char_is_element == false && first_and_second_char_is_element == true)
                {
                    elem.element = elems.find(temp_str);
                    i++;
                }
                
                //We assume that co2 = CO2
                else if(first_char_is_element == true && first_and_second_char_is_element == true)
                {
                    elem.element = elems.find(std::string(1, std::toupper(comp_in[i])));
                    i++;
                }
                
                else if(first_and_second_char_is_element == false && first_char_is_element == false)
                {
                    throw std::invalid_argument("Element symbol could not be interpreted from input: " + comp_in);
                }
                
            }
            
            
            else if(isupper(comp_in[i]))
            {
                if(islower(comp_in[i+1]))
                {
                    string_buffer += comp_in[i];
                    string_buffer += comp_in[i+1];
                    
                    try { elems.find(string_buffer); }
                    catch(const std::invalid_argument &e)
                    {
                        throw std::invalid_argument("Invalid element symbols:" + std::string(2, (comp_in[i] + comp_in[i+1])));
                    }
                    
                    elem.element = elems.find(string_buffer);
                    i++;
                }
                
                else
                {
                    try { elems.find(std::string(1, comp_in[i])); }
                    catch(const std::invalid_argument &e)
                    {
                        throw std::invalid_argument("Invalid element symbol:" + std::string(1, (comp_in[i])));
                    }
                    
                    elem.element = elems.find(std::string(1, comp_in[i]));
                }
                
            }
            
            //Check if element has mulitplier.
            if(isdigit(comp_in[i+1]))
            {
                std::string digit_buffer = "";
                
                int cur_pos = i+1;
                for(int m = 0; isdigit(comp_in[cur_pos+m]) && m < comp_in.size(); m++)
                {
                    digit_buffer.push_back(comp_in[cur_pos+m]);
                    i++;
                }
                
                elem.count = std::stoi(digit_buffer);
            }
            else
                elem.count = 1;
            
            
            compound_data.push_back(elem);
        }
        
        
        //A parenthesis means we will branch into another node.
        else if(comp_in[i] == '(' || comp_in[i] == '[')
        {
            int paranthesis_buffer = 1;
            
            while(paranthesis_buffer != 0)
            {
                if(comp_in[i+1] == '(' || comp_in[i+1] == '[')
                    paranthesis_buffer++;
                
                else if(comp_in[i+1] == ')' || comp_in[i+1] == ']')
                    paranthesis_buffer--;
                
                if(paranthesis_buffer != 0)
                    string_buffer.push_back(comp_in[i+1]);
                
                
                //Paranthesis mismatch:
                if(i+1 == comp_in.size())
                {
                    throw std::invalid_argument(std::string("Paranthesis mismatch in expression ") + comp_in);
                }
                
                i++;
            }
            
            //Recursively parse new node
            Node<std::vector<element_count>>* child_node = parseCompound(string_buffer);
            int multiplier = 1;
            
            //check if node has multiplier
            if(isdigit(comp_in[i+1]))
            {
                std::string digit_buffer = "";
                
                int cur_pos = i+1;
                for(int m = 0; isdigit(comp_in[cur_pos+m]) && m < comp_in.size(); m++)
                {
                    digit_buffer.push_back(comp_in[cur_pos+m]);
                    i++;
                }
                
                multiplier = std::stoi(digit_buffer);

            }
            
            cur_node->addBranch(child_node, multiplier);
        }
        
        else if(comp_in[i] == '-')
        {
            //We want to ignore charges so we scan until non digit:
            if (i == comp_in.size())
            {
                //ignore it
                break;
            }
            
            i++;
            
            while (isdigit(comp_in[i]) && i != comp_in.size())
            {
                i++;
            }
        }
        
        //Invalid Character:
        else
        {
            throw std::invalid_argument(std::string("Invalid character ") += comp_in[i] + std::string("' in expression ") + comp_in);
        }
        
        string_buffer.clear();
        
    }
    
    cur_node->setData(compound_data);
    return cur_node;
}


reaction_data parseReactionToStrings(std::string reaction)
{
    reaction_data parsed_data;
    std::string compound_buffer = "";
    unsigned int compound_multiplier = 1;
    
    //Checks if "reaction" is just a number
    bool numberError = true;
    for(int i = 0; i < reaction.size(); i++)
    {
        if(!isdigit(reaction[i]))
        {
            numberError = false;
        }
    }
    
    //Make sure we have arrow
    bool arrowError = true;
    for(int i = 0; i < reaction.size()-1; i++)
    {
        if(reaction[i] == '-' && reaction[i+1] == '>')
        {
            arrowError = false;
        }
    }
    
    if(numberError || arrowError)
    {
        throw std::invalid_argument(std::string("Number error"));
    }
    
    
    //Remove whitespaces:
    std::string::iterator end_pos = std::remove(reaction.begin(), reaction.end(), ' ');
    reaction.erase(end_pos, reaction.end());
    
    bool expect_multiplier = true;
    bool passed_arrow = false;
    for(int i = 0; i < reaction.size(); i++)
    {
        char current_char = reaction[i];
        
        //Copy down full number;
        if(expect_multiplier == true && isdigit(current_char))
        {
            std::string digit_buffer = "";
            digit_buffer += current_char;
            i++;
            
            while(isdigit(reaction[i]))
            {
                digit_buffer += reaction[i];
                i++;
            }
            
            i--;
            
            compound_multiplier = std::stoi(digit_buffer);
            expect_multiplier = false;
        }
        
        else if(isalnum(current_char) || current_char == '(' || current_char == ')' || current_char == '[' || current_char == ']')
        {
            compound_buffer.push_back(current_char);
            expect_multiplier = false;
        }
        
        else if(current_char == '+')
        {
            if(passed_arrow == false)
                parsed_data.lhs.push_back(std::make_pair(compound_multiplier, compound_buffer));
            
            if(passed_arrow == true)
                parsed_data.rhs.push_back(std::make_pair(compound_multiplier, compound_buffer));
            
            compound_multiplier = 1;
            expect_multiplier = true;
            compound_buffer.clear();
        }
        
        else if(current_char == '-')
        {
            if(reaction[i+1] == '>')
            {
                parsed_data.lhs.push_back(std::make_pair(compound_multiplier, compound_buffer));
                
                
                passed_arrow = true;
                compound_multiplier = 1;
                expect_multiplier = true;
                compound_buffer.clear();
                i++;
            }
            
            else
            {
                throw std::invalid_argument(std::string("Invalid character '") += current_char + std::string("' in expression " + reaction));
            }
        }
        
        //Invalid
        else
        {
            throw std::invalid_argument(std::string("Invalid character '") += current_char + std::string("' in expression " + reaction));
        }
        
        
        
    }
    
    parsed_data.rhs.push_back(std::make_pair(compound_multiplier, compound_buffer));
    
    
    return parsed_data;
}




