//Showcases some sample functionality.


#include <iostream>

#include "Compound.hpp"
#include "Reaction.hpp"

int main()
{
	while(true)
	{
		int choice;
		std::cout<<"1. Compound" << std::endl << "2. Reaction" << std::endl << std::endl << "Selection : ";
		std::cin >> choice;

		if(choice == 1)
		{
			std::string comp;
			std::cout << std::endl << std::endl <<"Enter Compound Formula : ";
			std::cin >> comp;

			Compound compound(comp);
			std::string mm = std::to_string(compound.molar_mass_total());
			std::string emp_comp = compound.getEmpiricalCompound().compoundString();
			std::map<ElementBase, double> mm_p = compound.mass_percent_element();

			std::cout << std::endl << std::endl << "Molar Mass : " << mm << std::endl;
			std::cout << "Empirical Compound : " << emp_comp << std::endl << std::endl;
			std::cout << "-----------Molar Mass Percents----------" << std::endl;

			for(std::map<ElementBase, double>::const_iterator it = mm_p.begin(); it != mm_p.end(); it++)
				std::cout << it->first.symbol() << " : " << it->second << std::endl;

		}

		if(choice == 2)
		{
			std::string reac;
			std::cout << std::endl << std::endl << "Enter Reaction : " << std::endl;
			std::cin>>reac;

			Reaction reaction(reac);
			std::map<Compound*, unsigned int> balanced = reaction.getBalanced();
			std::cout << std::endl << "------------Balance Solution-------------" << std::endl;

			for(std::map<Compound*, unsigned int>::const_iterator it = balanced.begin(); it != balanced.end();
					it++)
				std::cout << it->first->compoundString() << " : " << it->second << std::endl;
		}

		else
		{
			break;
		}
	}
}
