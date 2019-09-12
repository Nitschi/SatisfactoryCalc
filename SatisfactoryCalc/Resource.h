#pragma once

#include <string>

enum ResourceType{Nothing, IronOre, LimeStone, Coal, Concrete, IronIngot, SteelIngot, SteelPipe, SteelBeam, EncasedIndustrialBeam, IronPlate, IronRod, Screw, ReinforcedIronPlate};

struct Resource
{
	ResourceType type;
	double amount;

	bool operator < (const Resource& res) const
	{
		return (amount < res.amount);
	}
};
