#include "YamlReader.h"
#include <iostream>
#include <filesystem>


ResMap YamlReader::loadResMap(std::string filename)
{
	std::ifstream fin(filename);
	YAML::Node node = YAML::Load(fin);

	return nodeMapToResMap(node);
}

ResMap YamlReader::nodeMapToResMap(YAML::Node node)
{
	ResMap res_map;
	for (YAML::const_iterator it = node.begin(); it != node.end(); ++it)
	{
		res_map.insert({ it->first.as<std::string>(), it->second.as<double>() });
	}
	return res_map;
}

std::vector<Recipe> YamlReader::loadRecipes(std::string filename)
{
	std::ifstream fin(filename);
	YAML::Node node = YAML::Load(fin);

	std::vector<Recipe> recipeVec;

	for (YAML::const_iterator recipeIt = node.begin(); recipeIt != node.end(); ++recipeIt)
	{
		// TODO: use recipe : node syntax
		Resource output = {recipeIt->begin()->first.as<std::string>() , recipeIt->begin()->second["Amount"].as<double>() };

		double time { recipeIt->begin()->second["Time"].as<double>() };
		
		ResMap in = nodeMapToResMap(recipeIt->begin()->second);

		// TODO: Check if recipe only depends on previously defined resources
		in.erase("Amount");
		in.erase("Time");

		Recipe recipe(in, output, time);

		recipeVec.push_back(recipe);
	}

	return recipeVec;

}

std::vector<Recipe> YamlReader::overwriteAltRecipes(std::vector<Recipe> defaultRecipes, std::vector<Recipe> altRecipes)
{
	std::vector<Recipe> myRecipes = defaultRecipes;
	for (auto& altRecipe : altRecipes)
	{
		for (auto& myRecipe : myRecipes)
		{
			if (altRecipe.out.first == myRecipe.out.first) 
			{
				myRecipe = altRecipe;
			}
		}
	}
	return myRecipes;
}
