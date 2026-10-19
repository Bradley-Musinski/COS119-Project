#include "Player.h"
#include "Screens.h"

void Player::PrintStats() const
{
	const std::size_t width = 40; // inner width of the border

	const std::string title = charStats.Name + " the " + charStats.ClassName;
	const std::string border = "  ##" + std::string(width, '=') + "##";

	// Center the title (if it's too long, just don't pad it)
	const std::size_t totalWidth = width + 8;
	const std::size_t padAmount = title.size() < totalWidth ? (totalWidth - title.size()) / 2 : 0;
	const std::string titlePad(padAmount, ' ');

	GEngine->Print(border, Color::BMagenta, 1);
	GEngine->Print(titlePad + title, Color::BMagenta, 1);
	GEngine->Print(border, Color::BMagenta, 2);

	GEngine->Print("    \033[1mHP      : \033[22m" + std::to_string(charStats.Health), Color::Green, 1);
	GEngine->Print("    \033[1mAC      : \033[22m" + std::to_string(charStats.ArmorClass), Color::Green, 1);
	GEngine->Print("    \033[1mStamina : \033[22m" + std::to_string(charStats.Stamina), Color::Green, 2);

	GEngine->Print("    \033[1mAbilities: \033[22m", Color::Green, 0);

	for (const CharacterAbility& ability : charAbilities.abilities)
	{
		const std::string effect =
			ability.Damage > 0 ? "Damage " + std::to_string(ability.Damage) :
			ability.Health > 0 ? "Heals " + std::to_string(ability.Health) :
			ability.Armor > 0 ? "Armor +" + std::to_string(ability.Armor) :
			"No effect";

		GEngine->Print(ability.Name + ": " + effect, Color::Green, 0);
		GEngine->Print("\n\t\t\033[3m" + ability.Desc + "\033[0m", Color::Gray, 1);
		GEngine->Print("\t      ", Color::Gray, 0);
	}

	GEngine->PrintBlankLines(1);
	GEngine->Print(border, Color::BMagenta, 2);
}
