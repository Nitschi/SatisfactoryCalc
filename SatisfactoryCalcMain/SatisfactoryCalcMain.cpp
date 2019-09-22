// SatisfactoryCalcMain.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <iomanip>

#include "yaml-cpp/yaml.h"

#include "../SatisfactoryCalc/Resource.h"
#include "../SatisfactoryCalc/Factory.h"
#include "../SatisfactoryCalc/YamlReader.h"




int main()
{
	YamlReader reader;
	std::vector<Recipe> withAltRecipes = reader.overwriteAltRecipes(reader.loadRecipes("default_recipes.yaml"),
		reader.loadRecipes("alternative_recipes.yaml"));
	Factory factory(withAltRecipes);
	ResMap constraints = reader.loadResMap("constraints.yaml");
	ResMap desired = reader.loadResMap("desired.yaml");

	ResMap allIngredients = factory.calcAllIngredients(desired);
	ResMap possible = factory.calcPossibleIngredients(constraints, allIngredients);
	ResMap factories = factory.calcNecessaryFactories(possible);

	std::cout << std::endl << "========" << std::endl << "CONSTRAINTS:" << std::endl << "========" << std::endl;
	
	factory.printResMap(constraints);

	std::cout << std::endl << "========" << std::endl << "DESIRED:" << std::endl << "========" << std::endl;
	factory.printResMap(desired);

	std::cout << std::endl << "========" << std::endl << "POSSIBLE:" << std::endl << "========" << std::endl;
	factory.printResMap(possible);

	std::cout << std::endl << "========" << std::endl << "FACTORIES:" << std::endl << "========" << std::endl;
	factory.printResMap(factories);

	std::cin.get();
	return 0;
}






