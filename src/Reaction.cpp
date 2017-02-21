//
//  Reaction.cpp
//  Chemistry
//
//  Created by Jose Bouza on 6/27/16.
//  Copyright © 2016 Jose Bouza. All rights reserved.
//

#include "Reaction.hpp"

Reaction::Reaction(std::string reaction)
{
    //Parse to strings
    reaction_data reaction_d;
    try { reaction_d = parseReactionToStrings(reaction); }
    catch(const std::invalid_argument& e)
    {
        throw std::invalid_argument("Number error");
    }
    
    Reaction::reaction_name = reaction;
    Reaction::brute_solution_bound = 40;
    Reaction::matrix_solution_bound = 1000;
    
    //Parse to native structure:
    unsigned int i = 0;
    for(std::pair<unsigned int, std::string> compound_string : reaction_d.lhs)
    {
        try
        {
            Compound comp(compound_string.second, i);
            Reaction::balance_solution.push_back(compound_string.first);
            Reaction::lhs.push_back(comp);
        }
        
        catch(const std::invalid_argument& e){throw e;}
        
        i++;
    }
    
    for(std::pair<unsigned int, std::string> compound_string : reaction_d.rhs)
    {
        try
        {
            Compound comp(compound_string.second, i);
            Reaction::balance_solution.push_back(compound_string.first);
            Reaction::rhs.push_back(comp);
        }
        
        catch(const std::invalid_argument& e){throw e;}
        
        i++;
    }
    
    Reaction::complete_reaction.insert(Reaction::complete_reaction.end(), Reaction::lhs.begin(), Reaction::lhs.end());
    Reaction::complete_reaction.insert(Reaction::complete_reaction.end(), Reaction::rhs.begin(), Reaction::rhs.end());
    
    if(!Reaction::Equals(Reaction::lhs, Reaction::rhs, Reaction::balance_solution))
        if(!Reaction::Balance())
            throw std::invalid_argument("Could not balance reaction.");
    
    Reaction::balance_id();

    
}

Reaction::Reaction(std::vector<Compound> lhs, std::vector<Compound> rhs)
{
    Reaction::lhs = lhs;
    Reaction::rhs = rhs;
    
    if(!Reaction::Equals(Reaction::lhs, Reaction::rhs, Reaction::balance_solution))
        if(!Reaction::Balance())
            throw std::invalid_argument("Could not balance reaction.");
}

std::string Reaction::reactionName()
{
    return Reaction::reaction_name;
}

void Reaction::balance_id()
{
    unsigned int i = 0;
    for(std::vector<Compound>::iterator it = Reaction::complete_reaction.begin(); it != Reaction::complete_reaction.end(); it++)
    {
        balance_solutions_id[it->getCompID()] = Reaction::balance_solution[i];
        i++;
    }
}

//Consider a more efficient solution. This alogirithm is used very heavily in finding a solution

bool Reaction::Equals(std::vector<Compound> lhs, std::vector<Compound> rhs, std::vector<unsigned int> coefficients)
{
    std::vector<element_count> lhs_count;
    std::vector<element_count> rhs_count;
    
    if(lhs.size() + rhs.size() == coefficients.size())
    {
        for(int m = 0; m < lhs.size(); m++)
        {            
            //Add each element_count in comp to lhs_count. We will merge at the end
            for(auto i = lhs[m].begin(); i != lhs[m].end(); ++i)
            {
                //Is dereferencing less efficient?
                element_count element = *i;
                element.count *= coefficients[m];
                lhs_count.push_back(element);
            }
        }
        
        for(int m = 0; m < rhs.size(); m++)
        {
            for(auto i = rhs[m].begin(); i != rhs[m].end(); ++i)
            {
                //Is dereferencing less efficient?
                element_count element = *i;
                element.count *= coefficients[lhs.size()+m];
                rhs_count.push_back(element);
            }
        }
        
        std::vector<element_count> lhs_final = mergeData(lhs_count);
        std::vector<element_count> rhs_final = mergeData(rhs_count);
        
        std::sort(lhs_final.begin(), lhs_final.end(), compareElementCount);
        std::sort(rhs_final.begin(), rhs_final.end(), compareElementCount);
        
        //Check if two sides are equal
        if(lhs_final.size() == rhs_final.size())
        {
            for(int i = 0; i < lhs_final.size(); i++)
            {
                if(!(lhs_final[i] == rhs_final[i]))
                {
                    return false;
                }
            }
            
            return true;
        }
        
        else
            return false;
    }
    
    else
    {
        throw std::invalid_argument("Reaction balance algorithm error: Mismatch between compound count and coefficient count");
    }
    
}


//This is a recursive algorithim that descends a permutation tree to generate a solution space. In more abstract terms, it generates an n-dimensional
//cube of length checkbound with every possible permutation of number 1,...,checkbound. 

std::vector<std::vector<unsigned int>> Reaction::generateSolutionSpace(unsigned long dimensions, unsigned long check_bound)
{
  
    std::vector<std::vector<unsigned int>> current_solution_subspace;
    
    
    if(dimensions>1)
    {
        std::vector<std::vector<unsigned int>> solution_subspace_next = generateSolutionSpace(dimensions-1, check_bound);
        
        for(int i = 1; i <= check_bound; i++)
        {
            for(int m = 0; m < solution_subspace_next.size(); m++)
            {
                current_solution_subspace.push_back(solution_subspace_next[m]);
                current_solution_subspace.back().push_back(i);
            }
        }
    }
    
    
    //Generate identity subspaces
    else if(dimensions == 1)
    {
        std::vector<std::vector<unsigned int>> identity_subspace;
        
        for(int i = 1; i <= check_bound; i++)
        {
            std::vector<unsigned int> identity_subspace_element;
            identity_subspace_element.push_back(i);
            identity_subspace.push_back(identity_subspace_element);
        }
        
        current_solution_subspace = identity_subspace;
    }
    
    return current_solution_subspace;
}

arma::mat Reaction::solveBalanceMatrix()
{
    //Get number of rows:
    std::map<ElementBase, int> unique_elements;
    
    int i = 0;
    for(Compound comp : Reaction::complete_reaction)
    {
        for(Compound::iterator comp_it = comp.begin(); comp_it != comp.end(); comp_it++)
        {
            if(  unique_elements.find(comp_it->element) == unique_elements.end() )
            {
                unique_elements[comp_it->element] = i;
                i++;
            }
        }
        
    }
    
    unsigned long num_rows = unique_elements.size();
    unsigned long num_colunms = complete_reaction.size();
    
    //Reserve and generate matrix:
    arma::mat A = arma::zeros<arma::mat>(num_rows, num_colunms);
    
    //Populate matrix:
    int col = 0;
    
    for(Compound comp : Reaction::lhs)
    {
        for(Compound::iterator comp_it = comp.begin(); comp_it != comp.end(); comp_it++)
        {
            for(auto elem_it = unique_elements.begin(); elem_it != unique_elements.end(); elem_it++)
            {
                if(comp_it->element == elem_it->first)
                {
                    A.at(elem_it->second, col) = comp_it->count;
                }
            }
        }
        col++;
    }
    
    for(Compound comp : Reaction::rhs)
    {
        for(Compound::iterator comp_it = comp.begin(); comp_it != comp.end(); comp_it++)
        {
            for(auto elem_it = unique_elements.begin(); elem_it != unique_elements.end(); elem_it++)
            {
                if(comp_it->element == elem_it->first)
                {
                    A.at(elem_it->second, col) = -comp_it->count;
                }
            }
        }
        col++;
    }
    try
    {
        arma::vec x1 = arma::null(A);
        return x1;
    }
    catch(...)
    {
        throw std::invalid_argument("Matrix Initalization Error");
    }
}


std::vector<unsigned int> Reaction::parseMatrixSolve(arma::mat X)
{
    
    std::vector<double> solution_basis_vector = {*(X.begin())};
    double min_value = *(X.begin());
    //Convert matrix to c++ vector and find smallest value
    for(arma::mat::iterator it = X.begin() + 1; it != X.end(); it++)
    {
        if( (*it) < min_value )
            min_value = *it;
        
        solution_basis_vector.push_back(*it);
    }
    
    for(double& n : solution_basis_vector)
    {
        //Make vector standard
        n = n*1.0/min_value;
    }
    
    
    for(int c = 1; c < Reaction::matrix_solution_bound; c++)
    {
        //Make a copy of the matrix and multiply
        std::vector<double> solution_bv_c = solution_basis_vector;
        std::vector<unsigned int> solution_bv_c_int;
        
        for(double n : solution_bv_c)
        {
            solution_bv_c_int.push_back(std::round(n*c));
        }
        
        if(Equals(Reaction::lhs, Reaction::rhs, solution_bv_c_int))
        {
            
            return solution_bv_c_int;
        }
    }
    
    throw std::invalid_argument("Matrix output invalid.");
}


bool Reaction::matrixBalance()
{
    arma::mat x;
    try { x = Reaction::solveBalanceMatrix(); }
    catch(...) { return false; }
    
    try { Reaction::balance_solution = Reaction::parseMatrixSolve(x); }
    catch(...)
    {
        return false;
    }
    
    return true;
}


bool Reaction::bruteBalance()
{
    unsigned long compound_count = Reaction::lhs.size() + Reaction::rhs.size();
    
    //We populate the solution space with every possible solution and check after
    std::vector<std::vector<unsigned int>> solution_space = generateSolutionSpace(compound_count, Reaction::brute_solution_bound/Reaction::complete_reaction.size());
    
    for(int i = 0; i < solution_space.size(); i++)
    {
        if(Reaction::Equals(Reaction::lhs, Reaction::rhs, solution_space.at(i)))
        {
            balance_solution = solution_space.at(i);
            return true;
        }
    }
    
    return false;
}

bool Reaction::Balance()
{
    if(Reaction::matrixBalance() == false)
    {
        return false;
        
        //if(Reaction::bruteBalance() == false)
           // return false;
    }
    
    return true;
}


std::map<Compound*, unsigned int> Reaction::getBalanced()
{
    std::map<Compound*, unsigned int> output;
    
    for(int i = 0; i < Reaction::balance_solution.size(); i++)
    {
        output[ &Reaction::complete_reaction[i] ] = Reaction::balance_solution[i];
    }
    
    return output;
}

stoich_analysis_type Reaction::classifyStoichAnalysis(std::map<Compound*, double> in)
{
    
    //We remove doubles that equal zero because those signify compounds that we want to calculate for.
    for(std::map<Compound*, double>::iterator it = in.begin(); it != in.end(); it++)
    {
        if(it->second == 0)
        {
            in.erase(it);
            it--;
        }
    }
    
    unsigned long lhs_end = Reaction::lhs.size();
    unsigned long total_size = Reaction::complete_reaction.size();
    
    if(in.size() == 1)
    {
        return SINGLE_REACTANT;
    }
    
    else if(in.size() < total_size)
    {
        return LIMITING_REACTANT_PRODUCT;
    }
    
    else
    {
        throw std::invalid_argument("Stoich Analysis Error: Invalid input arguments greater than reaction.");
    }
}


std::map<Compound*, double> Reaction::stoichAnalysis(std::vector<double> data_in)
{
    //Verify the input and maps to the internal compounds
    std::map<Compound*, double> stoich_map;
    
    if(data_in.size() <= Reaction::complete_reaction.size())
    {
        for(int i = 0; i < data_in.size(); i++)
        {
            stoich_map[ &Reaction::complete_reaction[i] ] = data_in[i];
        }
    }
    
    else
    {
        throw std::invalid_argument("Stoich Analysis Error: Invalid input arguments greater than reaction.");
    }
    
    return Reaction::stoichAnalysis(stoich_map);
}

//This algorithm will find a limiting reactant OR product. If the limiting compound is a reactant it will procede
//as you would expect and caluclate values for the products. If the limiting compound is a product it will run the reaction
//backwards and treat the product as a limiting reactant in the opposite reaction.
std::map<Compound*, double> Reaction::stoichAnalysis(std::map<Compound*, double> data_in)
{
    std::map<Compound*, double> output_reaction;
    
    //Check that compound list given is compatible with internal reaction.
    for(std::map<Compound*, double>::iterator it = data_in.begin(); it != data_in.end(); it++)
    {
        bool matched = false;
        for(std::vector<Compound>::iterator it2 = Reaction::complete_reaction.begin(); it2 != Reaction::complete_reaction.end(); it2++)
        {
            Compound* comp = it->first;
            if((comp->getCompID() == (*it2).getCompID()))
            {
                matched = true;
            }
        }
        
        if(matched == false)
        {
            throw std::invalid_argument("Stoich Analysis Error: Generated compound list not compatible with internal reaction");
            
        }
    }
    
    
    stoich_analysis_type analysis_classification = classifyStoichAnalysis( data_in );
    
    
    std::map<Compound*, unsigned int> balanced_solution = Reaction::getBalanced();
    if(analysis_classification == SINGLE_REACTANT)
    {
        std::pair<Compound*, double> reactant_amount;
        
        for(std::map<Compound*, double>::iterator it = data_in.begin(); it != data_in.end(); it++)
        {
            if(it->second != 0)
            {
                reactant_amount.first = it->first;
                reactant_amount.second = it->second;
                break;
            }
        }
        
        for(std::map<Compound*, double>::iterator it = data_in.begin(); it != data_in.end(); it++)
        {
            //Stoichiometric ratio
            output_reaction[ it->first ] = reactant_amount.second*(balance_solutions_id[ it->first->getCompID() ] / balance_solutions_id[ reactant_amount.first->getCompID() ]);
        }
        
    }
    
    else if(analysis_classification == LIMITING_REACTANT_PRODUCT)
    {
        
        Compound* limiting_comp = (data_in.begin()->first);
        bool limiting_reactant = true;

        //We divide by coefficients to standarizes compound and find limiting reactant
        int i = 0;
        for(std::map<Compound*, double>::iterator it = data_in.begin(); it != data_in.end(); it++)
        {
            it->second *= 1.0/(Reaction::balance_solutions_id[it->first->getCompID()]);
            
            if(it->second < data_in[limiting_comp] && it->second != 0)
            {
                if(i < Reaction::lhs.size())
                    limiting_reactant = true;
                else
                    limiting_reactant = false;
                
                limiting_comp = it->first;
            }
            
            i++;
        }
        
        
        double limiting_comp_amt = data_in[ limiting_comp ];
        i = 0;
        for(std::map<Compound*, double>::iterator it = data_in.begin(); it != data_in.end(); it++)
        {
            //Do nothing
            if((limiting_reactant == true &&  i < Reaction::lhs.size() && it->second == 0)
              ||(limiting_reactant == false && i >= Reaction::lhs.size() && it->second == 0));

            else if( (i < Reaction::lhs.size() && limiting_reactant == true) || (i >= (Reaction::lhs.size() ) && limiting_reactant == false ))
            {
                it->second -= limiting_comp_amt*balance_solutions_id[ it->first->getCompID()] / balance_solutions_id [ limiting_comp->getCompID() ];
            }
            
            else if( (i >= (Reaction::lhs.size()) && limiting_reactant == true) || (i < (Reaction::lhs.size()) && limiting_reactant == false ))
            {
                it->second += limiting_comp_amt*balance_solutions_id[ it->first->getCompID()] / balance_solutions_id [ limiting_comp->getCompID() ];
            }
            
            i++;
        }
        
        output_reaction = data_in;
    }
    
    
    return output_reaction;
}

std::map<unsigned int, double> Reaction::stoichAnalysis(std::map<unsigned int, double> data_in)
{
    std::map<Compound*, double> refactored_input;
    
    for(std::map<unsigned int, double>::iterator it = data_in.begin(); it != data_in.end(); it++)
    {
        for(std::vector<Compound>::iterator it2 = Reaction::complete_reaction.begin(); it2 != Reaction::complete_reaction.end(); it2++)
        {
            if( it->first == it2->getCompID())
            {
                refactored_input[ &(*it2) ] = it->second;
            }
        }
    }
    
    std::map<Compound*, double> output = Reaction::stoichAnalysis(refactored_input);
    
    std::map< unsigned int, double> output_proccesed;
    
    for( std::map<Compound*, double>::iterator it = output.begin(); it != output.end(); it++)
    {
        for(std::map<unsigned int, double>::iterator it2 = data_in.begin(); it2 != data_in.end(); it2++)
        {
            if( it->first->getCompID() == it2->first)
            {
                output_proccesed[it2->first] = it->second;
            }
        }
    }
    
    return output_proccesed;
    
}

