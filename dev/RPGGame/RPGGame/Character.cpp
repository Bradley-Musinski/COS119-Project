#include <iostream>
#include <string>
#include <vector>
#include "AActor.h"
#include "UMath.h"
#include "Character.h"
#include "GameEngine.h"
#include "Screens.h"
#include "Abilties.h"

int Character::RollInitiative()
{
	initiative = UMath::RandRange(1, 20);
	return initiative;
}



void Character::PrintStats() const
{}

