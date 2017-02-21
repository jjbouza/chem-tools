//
//  Reaction.hpp
//  Chemistry
//
//  Created by Jose Bouza on 6/27/16.
//  Copyright © 2016 Jose Bouza. All rights reserved.
//

#ifndef Reaction_hpp
#define Reaction_hpp

#include <utility> 
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <deque>
#include <cmath>
#include "parser.hpp"
#include "Compound.hpp"
#include "CompoundUtilities.hpp"

#define ARMA_DONT_USE_WRAPPER
#define ARMA_DONT_PRINT_ERRORS
#include <armadillo>


enum stoich_analysis_type {SINGLE_REACTANT, LIMITING_REACTANT_PRODUCT};

class Reaction
{
public:
    Reaction(std::string reaction);
    Reaction(std::vector<Compound> lhs, std::vector<Compound> rhs);
    
    std::map<Compound*, unsigned int> getBalanced();
    
    //Runs a stoichiometric analysis on a compound. For example: we set "in"
    //to be a map of 2 compounds with thier desired quantities. We then
    //produce the amounts of products that would be generated from a
    //reaction. Quantities are all in moles. 
    std::map<Compound*, double> stoichAnalysis(std::map<Compound*, double> in);
    std::map<Compound*, double> stoichAnalysis(std::vector<double> in);
    std::map<unsigned int, double> stoichAnalysis(std::map<unsigned int, double>);
    
    std::string reactionName();
    
private:
    
    std::vector<Compound> lhs;
    std::vector<Compound> rhs;
    
    std::string reaction_name;
    
    //lhs+rhs:
    std::vector<Compound> complete_reaction;
    
    std::vector<unsigned int> balance_solution;
    
    std::map<unsigned int, unsigned int> balance_solutions_id;
    
    //Bound for solution space searcher
    unsigned int brute_solution_bound;
    unsigned int matrix_solution_bound;
    
    
    //Checks if two sides of reaction satisfy conditions of reaction.
    bool Equals(std::vector<Compound> lhs, std::vector<Compound> rhs, std::vector<unsigned int> coefficients);
    bool Equals(std::vector<Compound> lhs, std::vector<Compound> rhs, arma::mat coefficients);
    
    
    //Attempts to balance checmical equation. Currently uses brute force methods. 
    bool Balance();
    
    void balance_id();
    
    bool bruteBalance();
    bool matrixBalance();
    
    //Dimensions is the number of compounds in the reaction. This generates the solution space
    //for the brute-force balancing function. We return a pointer to avoid copying
    //such a large data structure. 
    std::vector<std::vector<unsigned int>> generateSolutionSpace(unsigned long dimensions, unsigned long bound_check);
    
    stoich_analysis_type classifyStoichAnalysis(std::map<Compound*, double> in);
    
    //General algorithm for balancing an algorithm using linear algebraic methods
    arma::mat solveBalanceMatrix();
    //Checks if a solution consists of elements that are approximately integers.
    bool validSolution(arma::mat X);
    //Parses raw matrix solution
    std::vector<unsigned int> parseMatrixSolve(arma::mat X);
    
};

#endif /* Reaction_hpp */
