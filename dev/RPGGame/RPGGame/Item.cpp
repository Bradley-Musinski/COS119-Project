#include "Item.h"
#include "Character.h"
#include "Umath.h"

void Item::UseItem(Character& character)
{
	if (ItemData.Type == ItemType::Consumable)
	{
		character.charStats.Health = UMath::Clamp(character.charStats.Health + ItemData.Amount, 0, character.charStats.MaxHealth);
	}
}
