#pragma once
#include "Enemy.h"
#include "UMath.h"

class Kobald : public Enemy
{
public:
	Kobald()
	{
		charStats.Name = "Kobald";
		charStats.ClassName = "Enemy_Kobald";
		charStats.MaxHealth = UMath::RandRange(60, 75);
		charStats.Health = charStats.MaxHealth;
		charStats.Attack = UMath::RandRange(14, 17);
		charStats.ArmorClass = UMath::RandRange(2, 5);
		charStats.Stamina = UMath::RandRange(11, 15);
		charStats.Exp = UMath::RandRange(10, 15);

		RollInitiative();

		GEngine->RegisterActor(this);
	}
};

