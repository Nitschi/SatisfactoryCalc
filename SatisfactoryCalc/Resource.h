#pragma once

#include <string>

enum ResourceType{Nothing, IronOre, IronIngot, IronPlate, IronRod, Screw, ReinforcedIronPlate};

struct Resource
{
	ResourceType type;
	double amount;
};
