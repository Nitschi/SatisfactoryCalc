#include "Factory.h"
#include <assert.h>

#include <iostream>



Factory::Factory() {
	Resource no{ Nothing, 0 };		// no second input material

		allRecipes = {
			{IronIngot,			{{IronOre, 1},			no,			{IronIngot, 1}}},
			{IronPlate,			{{IronIngot, 2},		no,			{IronPlate, 1}}},
			{IronRod,			{{IronIngot, 1},		no,			{IronRod, 1}}},
			{Screw,				{{IronRod, 1},			no,			{Screw, 6}}},
			{ReinforcedIronPlate,{{IronPlate, 4},	{Screw, 24},	{ReinforcedIronPlate, 1}}}
	};

		desiredResources = {
			{ReinforcedIronPlate, 1}
		};


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


std::list<Resource> Factory::calcAllResources()  // calculate all intermediate resources from the desired backwards
{
	for (auto& res : desiredResources) // access by reference to avoid copying
	{
		allResources[res.type] += res.amount;
		std::cout << res.type << std::endl;
		std::cout << res.amount << std::endl;
	}

	// TODO: use backwards to get amount of ingredients

	


	return std::list<Resource>();
}
