#include "Factory.h"
#include "Resource.h"
#include <assert.h>

#include <iostream>
#include <algorithm>
#include <assert.h>

std::vector<Resource> Factory::oneStepIngredients(Recipe recipe, Resource desOut)
{
	std::cout <<"Recipe: " << resourceNames[recipe.out.type] << std::endl;
	std::cout << "desout: " << resourceNames[desOut.type] << std::endl;

	if (desOut.type != recipe.out.type) {
		throw std::runtime_error("Wrong recipe(" + resourceNames[recipe.out.type] +") for this resource(" + resourceNames[desOut.type]+ ")");
	}

	std::vector<Resource> reqIn;

	for (auto input : recipe.in) {
		double amount = (input.amount / recipe.out.amount) * desOut.amount;
		Resource res{ input.type, amount };
		reqIn.push_back(res);
	}
	return reqIn;
}

void Factory::addRequiredProducts(std::vector<Resource> requiredRes, std::map<ResourceType,double>& currentResources) {

	for (Resource& res : requiredRes) {
		if (currentResources.find(res.type) == currentResources.end()) {  // resource needs to be added
			currentResources.insert({ res.type, res.amount });
		}
		else {		//resource already exists and amount needs to be added
			currentResources[res.type] += res.amount;
		}
	}
}


std::map<ResourceType, double> Factory::calcAllIngredients(std::map<ResourceType, double> desiredResources)  // calculate all intermediate resources from the desired backwards
{
	std::map<ResourceType, double> currentResources = desiredResources;
	std::map<ResourceType, double>::reverse_iterator highestProductIt = currentResources.rbegin();
	ResourceType highestProduct = highestProductIt->first;
	
	for (int i = highestProduct; i > 1; i--) 
	{
		ResourceType product = static_cast<ResourceType>(i);
		if (currentResources.count(product) == 1) {
			Recipe productRecipe = allRecipes[product];
			std::cout << "product " << resourceNames[productRecipe.in[0].type] << std::endl;
			Resource res{ product, currentResources[product] };

			addRequiredProducts(oneStepIngredients(productRecipe, res), currentResources);
		}
	}	

	return currentResources;
}

Factory::ResMap Factory::calcPossibleIngredients(ResMap productionConstraints, ResMap allIngredients) {
	// Production constraints should be given in Production per minute
	
	if (!productionConstraints.empty() && !allIngredients.empty()) {
		double limitingFactor = INFINITY;
		ResourceType limitingResource = Nothing;
		for (auto& constraint : productionConstraints) {
				double factor = constraint.second / allIngredients[constraint.first];
				if (factor < limitingFactor) {
					limitingResource = constraint.first;
					limitingFactor = factor;
				}
		}
		auto possibleIngredients = allIngredients;
		for (auto& ingredient : possibleIngredients) ingredient.second *= limitingFactor;
		std::cout << "Limiting Resource: " << limitingResource << std::endl;
		return possibleIngredients;
	}
	else {
		std::cout << "NO INGREDIENTS OR NO CONSTRAINTS GIVEN! EXITING" << std::endl;
		std::exit(EXIT_FAILURE);
	}
}

Factory::ResMap Factory::calcNecessaryFactories( ResMap possibleIngredients) {

	std::map<ResourceType, double> necessaryFactories;

	for (auto& ingredient : possibleIngredients) {
		double factoryNumber = (ingredient.second / allRecipes[ingredient.first].out.amount) * (allRecipes[ingredient.first].prodTime / 60);
		std::cout << (allRecipes[ingredient.first].prodTime / 60) << std::endl;
		necessaryFactories.insert(std::make_pair(ingredient.first, factoryNumber));
	}
	return necessaryFactories;
}
