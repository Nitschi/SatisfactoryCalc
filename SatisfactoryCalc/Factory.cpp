#include "Factory.h"
#include <assert.h>

#include <iostream>
#include <algorithm>
#include <assert.h>



Factory::Factory() {
	Resource no{ Nothing, 0 };		// no second input material

		allRecipes = {
			{IronOre,			{no, no, {IronOre, 1}}},
			{Coal,				{no, no, {Coal, 1}}},
			{LimeStone,			{no, no, {LimeStone, 1}}},
			{IronIngot,			{{IronOre, 1},			no,			{IronIngot, 1}}},
			{Concrete,			{{LimeStone, 3},		no,			{Concrete, 1}}},
			{IronPlate,			{{IronIngot, 2},		no,			{IronPlate, 1}}},
			{SteelIngot,		{{IronOre, 3},		{Coal, 3},		{SteelIngot, 2}}},
			{SteelPipe,			{{SteelIngot, 1},		no,			{SteelPipe, 1}}},
			{SteelBeam,			{{SteelIngot, 3},		no,			{SteelBeam, 1}}},
			{EncasedIndustrialBeam,{{SteelBeam, 4},	{Concrete,5},	{EncasedIndustrialBeam, 1}}},
			{IronRod,			{{IronIngot, 1},		no,			{IronRod, 1}}},
			{Screw,				{{IronRod, 1},			no,			{Screw, 6}}},
			{ReinforcedIronPlate,{{IronPlate, 4},	{Screw, 24},	{ReinforcedIronPlate, 1}}}
	};

		desiredResources = {
			{EncasedIndustrialBeam, 5},
			{SteelPipe, 15}
		};

		//std::sort(desiredResources.begin(), desiredResources.end());


}

std::vector<Resource> Factory::backward(Recipe recipe, Resource desOut)
{
	assert(desOut.type == recipe.out.type);
	Resource reqIn1;
	Resource reqIn2;
	reqIn1.type = recipe.in1.type;
	reqIn2.type = recipe.in2.type;
	reqIn1.amount = (recipe.in1.amount / recipe.out.amount) * desOut.amount;
	reqIn2.amount = (recipe.in2.amount / recipe.out.amount) * desOut.amount;
	return std::vector<Resource> {reqIn1, reqIn2};
}

void Factory::addRequiredProducts(std::vector<Resource> requiredRes, std::map<ResourceType,double>& currentResources) {

	for (Resource res : requiredRes) {
		if (currentResources.find(res.type) == currentResources.end()) {  // resource needs to be added
			currentResources.insert(std::make_pair(res.type, res.amount));
		}
		else {		//resource already exists and amount needs to be added
			currentResources[res.type] += res.amount;
		}
	}
}


std::map<ResourceType, double> Factory::calcAllResources()  // calculate all intermediate resources from the desired backwards
{
	std::map<ResourceType, double> currentResources = desiredResources;
	std::map<ResourceType, double>::iterator highestProductIt = currentResources.end();
	highestProductIt--;
	int highestProduct = highestProductIt->first;
	
	for (int i = highestProduct; i > 1; i--) {
		ResourceType product = static_cast<ResourceType>(i);
		if (currentResources.count(product) == 1) {
			Recipe productRecipe = allRecipes[product];
			Resource res{ product, currentResources[product] };

			addRequiredProducts(backward(productRecipe, res), currentResources);
		}
	}	

	return currentResources;
}
