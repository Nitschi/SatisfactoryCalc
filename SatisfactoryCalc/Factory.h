#pragma once

#include <list>
#include <map>
#include "Resource.h"
#include "Recipe.h"

class Factory
{
public:
	std::map<ResourceType, double> calcAllIngredients(std::map<ResourceType, double> desiredResources);
	std::map<ResourceType, double> calcPossibleIngredients(std::map<ResourceType, double> productionConstraints, std::map<ResourceType, double> allIngredients);
	std::vector<Resource> oneStepIngredients(Recipe recipe, Resource desOut);
	void addRequiredProducts(std::vector<Resource> requiredRes, std::map<ResourceType, double>& currentResources);
	Factory();

private:
	std::map<ResourceType, Recipe> allRecipes;
};