#include "pch.h"

#include "../SatisfactoryCalc/Factory.h"
#include "../SatisfactoryCalc/Recipe.h"
#include "../SatisfactoryCalc/Resource.h"

TEST(backwardTest, TestReinforcedIronPlates) {
	Factory myFactory = Factory();
	Recipe reinforcedIronPlatesRecipe{ {IronPlate, 4},	{Screw, 24},	{ReinforcedIronPlate, 1} };
	Resource desiredPlates{ ReinforcedIronPlate, 2 };
	std::vector<Resource> required = myFactory.oneStepIngredients(reinforcedIronPlatesRecipe, desiredPlates);

	EXPECT_EQ(required[0].amount, 8.0);
	EXPECT_EQ(required[0].type, IronPlate);

	EXPECT_EQ(required[1].amount, 48);
	EXPECT_EQ(required[1].type, Screw);
}

TEST(backwardTest, TestIronPlates) {

	Factory myFactory = Factory();
	Recipe ironPlatesRecipe { {IronIngot, 2}, {Nothing, 0}, {IronPlate, 1} };
	Resource desiredPlates{ IronPlate, 6 };
	std::vector<Resource> required = myFactory.oneStepIngredients(ironPlatesRecipe, desiredPlates );

	EXPECT_EQ(required[0].amount, 12.0);
	EXPECT_EQ(required[0].type, IronIngot);
}