#pragma once

#include <list>
#include <map>
#include "Recipe.h"


class Factory
{
public: 
	Factory(std::vector<Recipe> allRecipes);

	ResMap calcAllIngredients(ResMap desiredResources);
	ResMap calcPossibleIngredients(ResMap productionConstraints, ResMap allIngredients);
	ResMap calcNecessaryFactories(ResMap possibleIngredients);

	ResMap oneStepIngredients(Recipe recipe, Resource desOut);
	void addRequiredProducts(ResMap requiredRes, ResMap& currentResources);

	void printResMap(ResMap resmap);
	Recipe getRecipe(std::string resName);
	
	void setAllRecipes(std::vector<Recipe> allRecipes) { this->allRecipes = allRecipes; };

private:
	std::vector<Recipe> allRecipes;
};