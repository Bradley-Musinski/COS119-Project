#pragma once
#include "Enemy.h"
#include "UMath.h"

class Goblin : public Enemy
{
public:
	Goblin()
	{
		charStats.Name = "Goblin";
		charStats.ClassName = "Enemy_Goblin";
		charStats.Health = UMath::RandRange(6,9);
		charStats.Attack = UMath::RandRange(3, 6);
		charStats.ArmorClass = UMath::RandRange(2, 5);
		charStats.Stamina = UMath::RandRange(11, 15);
		charStats.Exp = UMath::RandRange(10, 15);

		RollInitiative();

		GEngine->RegisterActor(this);
	}
};

