#pragma once

#include <string>
#include <map>
#include <vector>

typedef std::map<std::string, double> ResMap;
typedef std::pair<std::string, double> Resource;

struct Recipe
{
	ResMap in;
	Resource out;
	double time;

	Recipe(ResMap input, Resource output, double prodTime)
	{
		in = input;
		out = output;
		time = prodTime;
	}
};