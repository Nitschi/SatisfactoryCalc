#pragma once

#include "Recipe.hpp"
#include "yaml-cpp/yaml.h"
#include <fstream>

namespace YamlReader
{
	ResMap loadResMap(std::string filename);
	ResMap nodeMapToResMap(const YAML::Node &node);
	std::vector<Recipe> loadRecipes(std::string filename);
	std::vector<Recipe> overwriteAltRecipes(const std::vector<Recipe> &defaultRecipes, const std::vector<Recipe> &altRecipes);
};