#pragma once

#include <list>
#include <map>
#include "Resource.h"
#include "Recipe.h"

class Factory
{
public:
	std::list <Resource> calcAllResources();
	std::vector<Resource> backward(Recipe recipe, Resource desOut);
	Factory();

private:
	std::map<ResourceType, Recipe> allRecipes;
	std::map<ResourceType, double> allResources;
	std::list<Resource> desiredResources;
};