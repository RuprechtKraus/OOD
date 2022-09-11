#include "Ducks/Duck.h"
#include <Behaviors/FlyBehaviors/FlyWithWingsBehavior.h>
#include <Ducks/DecoyDuck.h>
#include <Ducks/MallardDuck.h>
#include <Ducks/ModelDuck.h>
#include <Ducks/RedheadDuck.h>
#include <Ducks/RubberDuck.h>
#include <iostream>

void DrawDuck(Duck const& duck);
void PlayWithDuck(Duck& duck);

int main()
{
	MallardDuck mallardDuck;
	PlayWithDuck(mallardDuck);

	RedheadDuck redheadDuck;
	PlayWithDuck(redheadDuck);

	RubberDuck rubberDuck;
	PlayWithDuck(rubberDuck);

	DecoyDuck decoyDuck;
	PlayWithDuck(decoyDuck);

	ModelDuck modelDuck;
	PlayWithDuck(modelDuck);
	modelDuck.SetFlyBehavior(std::make_unique<FlyWithWingsBehavior>());
	PlayWithDuck(modelDuck);
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