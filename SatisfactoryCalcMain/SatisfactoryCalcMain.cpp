// SatisfactoryCalcMain.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>

#include "yaml-cpp/yaml.h"
/*
int main() {

	YAML::Emitter out;
	out << "Hello, World!";

	std::cout << "Here's the output YAML:\n" << out.c_str(); // prints "Hello, World!"
	std::cin.get();
	std::ofstream myfile;
	myfile.open("resources.yaml");
	myfile << out.c_str();
	myfile.close();

	return 0;
} */



#include "../SatisfactoryCalc/Resource.h"
#include "../SatisfactoryCalc/Factory.h"

ResMap loadResMap(std::string filename)
{
	std::ifstream fin(filename);
	YAML::Node node = YAML::Load(fin);

	ResMap res_map;
	for (YAML::const_iterator it = node.begin(); it != node.end(); ++it)
	{
		res_map.insert({ static_cast<ResourceType>(it->first.as<int>()), it->second.as<double>() });
	}

	return res_map;
}


 int main()
{
	Factory myFactory;

	ResMap constraints = loadResMap("constraints.yaml");

	ResMap desiredResources = loadResMap("desired.yaml");
	
	std::map<ResourceType, double> allResources = myFactory.calcAllIngredients(desiredResources);

	std::map<ResourceType, double> possibleResources = myFactory.calcPossibleIngredients(constraints, allResources);

	std::map<ResourceType, double> necessaryFactories = myFactory.calcNecessaryFactories(possibleResources);

	std::cout << std::endl << "CONSTRAINTS:" << std::endl << std::endl;
	for (auto& pair : constraints) {
		std::cout << "Type: " << resourceNames[pair.first] << " Amount: " << pair.second << std::endl;
	}

	std::cout << std::endl << "DESIRED:" << std::endl << std::endl;
	for (auto& pair : desiredResources) {
		std::cout << "Type: " << resourceNames[pair.first] << " Amount: " << pair.second << std::endl;
	}

	std::cout << std::endl << "POSSIBLE:" << std::endl << std::endl;

	for (auto& pair : possibleResources) {
		std::cout << "Type: " << resourceNames[pair.first] << " Amount: " << pair.second << std::endl;
	}

	std::cout << std::endl << "FACTORIES:" << std::endl << std::endl;
	for (auto& pair : necessaryFactories) {
		std::cout << "Type: " << resourceNames[pair.first] << " Amount: " << pair.second << std::endl;
	}

	std::cin.get();
	return 0;
}






