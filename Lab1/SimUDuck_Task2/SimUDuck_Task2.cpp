﻿#include "Ducks/Duck.h"
#include "Behaviors/FlyBehaviors/FlyWithWingsBehavior.h"
#include "Behaviors/FlyBehaviors/FlyWithRocketBehavior.h"
#include "Ducks/DecoyDuck.h"
#include "Ducks/MallardDuck.h"
#include "Ducks/ModelDuck.h"
#include "Ducks/RedheadDuck.h"
#include "Ducks/RubberDuck.h"
#include <iostream>

void DrawDuck(Duck const& duck);
void PlayWithDuck(Duck& duck);

int main()
{
	MallardDuck mallardDuck;
	mallardDuck.Fly();
	mallardDuck.Fly();
	mallardDuck.SetFlyBehavior(std::make_unique<FlyWithRocketBehavior>());
	mallardDuck.Fly();
	mallardDuck.Fly();
	mallardDuck.Fly();
	mallardDuck.SetFlyBehavior(std::make_unique<FlyWithWingsBehavior>());
	mallardDuck.Fly();
}

void DrawDuck(Duck const& duck)
{
	duck.Display();
}

void PlayWithDuck(Duck& duck)
{
	DrawDuck(duck);
	duck.Quack();
	duck.Fly();
	duck.Dance();
	std::cout << std::endl;
}