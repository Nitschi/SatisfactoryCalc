#pragma once

#include <list>
#include <map>
#include "Resource.h"

class Factory  // namespace would suffice
{
public: 
	typedef std::map<ResourceType, double> ResMap;
	ResMap calcAllIngredients(ResMap desiredResources);
	ResMap calcPossibleIngredients(ResMap productionConstraints, ResMap allIngredients);
	ResMap calcNecessaryFactories(ResMap possibleIngredients);
	std::vector<Resource> oneStepIngredients(Recipe recipe, Resource desOut);
	void addRequiredProducts(std::vector<Resource> requiredRes, std::map<ResourceType, double>& currentResources);

};