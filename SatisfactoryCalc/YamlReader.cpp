#include "YamlReader.hpp"
#include "Recipe.hpp"
#include <iostream>



ResMap YamlReader::loadResMap(std::string filename)
{
	std::ifstream fin(filename);
	YAML::Node node = YAML::Load(fin);

	return YamlReader::nodeMapToResMap(node);
}


ResMap YamlReader::nodeMapToResMap(const YAML::Node &node)
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

	//for (YAML::const_iterator recipeIt = node.begin(); recipeIt != node.end(); ++recipeIt)
	for (auto recipe : node)
	{
		Resource output {recipe.begin()->first.as<std::string>() , recipe.begin()->second["Amount"].as<double>() };
		double time { recipe.begin()->second["Time"].as<double>() };
		
		ResMap in = YamlReader::nodeMapToResMap(recipe.begin()->second);

		// TODO: Check if recipe only depends on previously defined resources
		in.erase("Amount");
		in.erase("Time");

		Recipe the_recipe(in, output, time);

		recipeVec.push_back(the_recipe);
	}
	return recipeVec;
}


std::vector<Recipe> YamlReader::overwriteAltRecipes(const std::vector<Recipe> &defaultRecipes, const std::vector<Recipe> &altRecipes)
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
