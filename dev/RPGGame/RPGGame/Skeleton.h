#pragma once
#include "Enemy.h"
#include "UMath.h"

class Skeleton : public Enemy
{
public:
	Skeleton()
	{
		charStats.Name = "Skeleton";
		charStats.ClassName = "Enemy_Skeleton";
		charStats.MaxHealth = UMath::RandRange(50, 65);
		charStats.Health = charStats.MaxHealth;
		charStats.Attack = UMath::RandRange(9, 14);
		charStats.ArmorClass = UMath::RandRange(2, 5);
		charStats.Stamina = UMath::RandRange(11, 15);
		charStats.Exp = UMath::RandRange(10, 15);

		RollInitiative();

		GEngine->RegisterActor(this);
	}
};

