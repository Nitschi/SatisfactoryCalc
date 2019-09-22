#pragma once

#include "Resource.h"
#include "yaml-cpp/yaml.h"
#include <fstream>

struct YamlReader
{
	ResMap loadResMap(std::string filename);
	ResMap nodeMapToResMap(YAML::Node node);
	std::vector<Recipe> loadRecipes(std::string filename);
	std::vector<Recipe> overwriteAltRecipes(std::vector<Recipe> defaultRecipes, std::vector<Recipe> altRecipes);
};