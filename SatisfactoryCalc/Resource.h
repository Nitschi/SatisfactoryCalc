#pragma once

#include <string>
#include <map>
#include <vector>


enum ResourceType {
	Nothing,
	Power,
	IronOre,
	CopperOre,
	LimeStone,
	Coal,
	IronIngot,
	IronPlate,
	IronRod,
	Screw,
	ReinforcedIronPlate,
	ModularFrame,
	Concrete,
	CopperIngot,
	Wire,
	Cable,
	SteelIngot,
	SteelPipe,
	SteelBeam,
	EncasedIndustrialBeam,
	HeavyModularFrame,
	Rotor,
	Stator,
	Motor
};

struct Resource
{
	ResourceType type;
	double amount;
};

struct Recipe
{
	std::vector<Resource> in;
	Resource out;
	double prodTime;
};

static std::map<ResourceType, std::string> resourceNames {
	{Nothing,					"Nothing"},
	{Power,						"Power"},
	{IronOre,					"Iron Ore"},
	{CopperOre,					"Copper Ore"},
	{LimeStone,					"Lime Stone"},
	{Coal,						"Coal"},
	{IronIngot,					"Iron Ingot"},
	{IronPlate,					"Iron Plate"},
	{IronRod,					"Iron Rod"},
	{Screw,						"Screw"},
	{ReinforcedIronPlate,		"Reinforced Iron Plate"},
	{ModularFrame,				"Modular Frame"},
	{Concrete,					"Concrete"},
	{CopperIngot,				"Copper Ingot"},
	{Wire,						"Wire"},
	{Cable,						"Cable"},
	{SteelIngot,				"Steel Ingot"},
	{SteelPipe,					"Steel Pipe"},
	{SteelBeam,					"Steel Beam"},
	{EncasedIndustrialBeam,		"Encased Industrial Beam"},
	{HeavyModularFrame,			"Heavy Modular Frame"},
	{Rotor,						"Rotor"},
	{Stator,					"Stator"},
	{Motor,						"Motor"}
};

static std::map<ResourceType, Recipe> allRecipes {
	{Power,						{{{Nothing, 0}},  {Power, 1}, 1}},
	{IronOre,					{{{Nothing, 0}},  {IronOre, 1}, 1}},
	{CopperOre,					{{{Nothing, 0}},  {CopperOre, 1}, 1}},
	{LimeStone,					{{{Nothing, 0}},  {LimeStone, 1}, 1}},
	{Coal,						{{{Nothing, 0}},  {Coal, 1}, 1}},
	{IronIngot,					{{{IronOre, 1}},		{IronIngot, 1}, 2}},
	{IronPlate,					{{{IronIngot, 2}},					{IronPlate, 1}, 4}},
	{IronRod,					{{{IronIngot, 1}},					{IronRod, 1}, 4}},
	{Screw,						{{{IronRod, 1}},						{Screw, 6}, 4}},
	{ReinforcedIronPlate,		{{{IronPlate, 4},	{Screw, 24}},	{ReinforcedIronPlate, 1}, 12}},
	{ModularFrame,				{{{ReinforcedIronPlate, 3},	{IronRod, 6}},	{ModularFrame, 1}, 15}},
	{Concrete,					{{{LimeStone, 3}},					{Concrete, 1}, 4}},
	{CopperIngot,				{{{CopperOre, 1}},		{CopperIngot, 1}, 2}},
	{Wire,						{{{CopperIngot, 1}},  {Wire, 3}, 4}},
	{Cable,						{{{Wire, 2}},  {Cable, 1}, 4}},
	{SteelIngot,				{{{IronOre, 3},		{Coal, 3}},		{SteelIngot, 2}, 4}},
	{SteelPipe,					{{{SteelIngot, 1}},					{SteelPipe, 1}, 4}},
	{SteelBeam,					{{{SteelIngot, 3}},					{SteelBeam, 1}, 6}},
	{EncasedIndustrialBeam,		{{{SteelBeam, 4},	{Concrete,5}},	{EncasedIndustrialBeam, 1}, 15}},
	{HeavyModularFrame,			{{{ModularFrame, 5},{SteelPipe,15},{EncasedIndustrialBeam,5},{Screw,90}},  {HeavyModularFrame, 1}, 30}},
	{Rotor,						{{{IronRod, 3}, {Screw, 22}},  {Rotor, 1}, 10}},
	{Stator,					{{{SteelPipe, 3},{Wire,10}},  {Stator, 1}, 10}},
	{Motor,						{{{Rotor, 2}, {Stator, 2}},  {Motor, 1}, 12}}
};
