#pragma once

#include <list>
#include <map>
#include "Resource.h"
#include "Recipe.h"

class Factory
{
public:
	std::map<ResourceType, double> calcAllResources();
	std::vector<Resource> backward(Recipe recipe, Resource desOut);
	void addRequiredProducts(std::vector<Resource> requiredRes, std::map<ResourceType, double>& currentResources);
	Factory();

private:
	std::map<ResourceType, Recipe> allRecipes;
	std::map<ResourceType, double> allResources;
	std::map<ResourceType, double> desiredResources;
};