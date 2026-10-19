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
		charStats.Health = UMath::RandRange(6, 9);
		charStats.Attack = UMath::RandRange(2, 5);
		charStats.ArmorClass = UMath::RandRange(2, 5);
		charStats.Stamina = UMath::RandRange(11, 15);
		charStats.Exp = UMath::RandRange(10, 15);

		RollInitiative();

		GEngine->RegisterActor(this);
	}
};

