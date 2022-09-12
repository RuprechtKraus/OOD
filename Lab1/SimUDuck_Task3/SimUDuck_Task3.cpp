#include "Behaviors/FlyBehavior.h"
#include "Ducks/DecoyDuck.h"
#include "Ducks/Duck.h"
#include "Ducks/MallardDuck.h"
#include "Ducks/ModelDuck.h"
#include "Ducks/RedheadDuck.h"
#include "Ducks/RubberDuck.h"
#include <iostream>

void DrawDuck(Duck const& duck);
void PlayWithDuck(Duck& duck);

int main()
{
	/*MallardDuck mallardDuck;
	PlayWithDuck(mallardDuck);

	RedheadDuck redheadDuck;
	PlayWithDuck(redheadDuck);

	RubberDuck rubberDuck;
	PlayWithDuck(rubberDuck);

	DecoyDuck decoyDuck;
	PlayWithDuck(decoyDuck);

	ModelDuck modelDuck;
	PlayWithDuck(modelDuck);
	modelDuck.SetFlyBehavior(GetFlyWithWingsBehavior());
	PlayWithDuck(modelDuck);*/

	MallardDuck mallardDuck;

	mallardDuck.Fly();
	mallardDuck.Fly();
	mallardDuck.SetFlyBehavior(GetFlyWithRocketBehavior());
	mallardDuck.Fly();
	mallardDuck.Fly();
	mallardDuck.Fly();
	mallardDuck.SetFlyBehavior(GetFlyWithWingsBehavior());
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