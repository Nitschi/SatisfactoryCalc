#include "Factory.h"
#include <assert.h>
#include <iostream>
#include <algorithm>
#include <assert.h>
#include <boost/range/adaptor/reversed.hpp>

ResMap Factory::oneStepIngredients(Recipe recipe, Resource desOut)
{

	if (desOut.first != recipe.out.first) {
		throw std::runtime_error("Wrong recipe(" + recipe.out.first +") for this resource(" + desOut.first + ")");
	}

	ResMap reqIn;

	for (auto& input : recipe.in) {
		double amount = (input.second / recipe.out.second) * desOut.second;
		Resource res { input.first, amount };
		reqIn.insert(res);
	}
	return reqIn;
}

Recipe Factory::getRecipe(std::string resName)
{
	for (auto recipe : allRecipes)
	{
		if (recipe.out.first == resName) {
			return recipe;
		}
	}
	std::cout << "Recipe for " << resName << " not found!" << std::endl;
}

void Factory::addRequiredProducts(ResMap requiredRes, ResMap& currentResources) 
{

	for (auto& res : requiredRes) {
		if (currentResources.find(res.first) == currentResources.end()) {  // resource needs to be added
			currentResources.insert({ res.first, res.second });
		}
		else {		//resource already exists and amount needs to be added
			currentResources[res.first] += res.second;
		}
	}
}


Factory::Factory(std::vector<Recipe> allRecipes)
{
	this->allRecipes = allRecipes;
}

ResMap Factory::calcAllIngredients(ResMap desiredResources)  // calculate all intermediate resources from the desired backwards
{
	ResMap currentResources = desiredResources;
	for(auto& recipe : boost::adaptors::reverse(allRecipes))  //iterate backwards through recipe list
	{
		std::string ResName = recipe.out.first;
		if (currentResources.find(ResName) != currentResources.end())
		{
			addRequiredProducts(oneStepIngredients(recipe, { ResName, currentResources[ResName] }), currentResources);
		}
	}
	return currentResources;
}

ResMap Factory::calcPossibleIngredients(ResMap productionConstraints, ResMap allIngredients) 
{
	// Production constraints should be given in Production per minute
	
	if (!productionConstraints.empty() && !allIngredients.empty()) 
	{
		double limitingFactor = INFINITY;
		std::string limitingResource = "Nothing";
		for (auto& constraint : productionConstraints) {
				double factor = constraint.second / allIngredients[constraint.first];
				if (factor < limitingFactor) {
					limitingResource = constraint.first;
					limitingFactor = factor;
				}
		}
		auto possibleIngredients = allIngredients;
		for (auto& ingredient : possibleIngredients) 
		{
			ingredient.second *= limitingFactor;
		}
		std::cout << "Limiting Resource: " << limitingResource << std::endl;
		return possibleIngredients;
	}
	else
	{
		std::cout << "NO INGREDIENTS OR NO CONSTRAINTS GIVEN! EXITING" << std::endl;
		std::exit(EXIT_FAILURE);
	}
}

ResMap Factory::calcNecessaryFactories( ResMap possibleIngredients) 
{

	ResMap necessaryFactories;

	for (auto& ingredient : possibleIngredients) {
		Recipe recipe = getRecipe(ingredient.first);
		double factoryNumber = (ingredient.second / recipe.out.second) * (recipe.time / 60);
		necessaryFactories.insert({ ingredient.first, factoryNumber });
	}
	return necessaryFactories;
}

void Factory::printResMap(ResMap resmap) 
{
	for (auto& recipe : allRecipes)
	{
		std::string resName = recipe.out.first;
		auto mapIt = resmap.find(resName);
		if (mapIt != resmap.end() && mapIt->second > 0)
		{
			int arrowLength = 25 - mapIt->first.length();
			if (arrowLength < 1) {arrowLength = 1;}

			std::cout << mapIt->first;
			std::cout << "  " << std::string(arrowLength, '-') << ">  ";
			std::cout << mapIt->second << std::endl;
		}
	}
}
