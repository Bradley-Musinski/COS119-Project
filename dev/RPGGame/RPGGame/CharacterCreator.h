#pragma once
#include "SaveSystem.h"
#include "Player.h"
#include "Dialogue.h"
#include "Input.h"
#include "CharacterTypes.h"


using namespace std::chrono_literals;

namespace CharacterCreator
{
	//Foward Declared
	void IsNameValid(std::string inputName, Player& player);

	void ApplyClass(Player& player, const CharacterTypes& charClass)
	{
		player.charStats.ClassName = charClass.Name;
		player.charStats.MaxHealth = charClass.Health;
		player.charStats.Health = player.charStats.MaxHealth;
		player.charStats.Attack = charClass.Attack;
		player.charStats.ArmorClass = charClass.ArmorClass;
		player.charStats.Stamina = charClass.Stamina;
		player.charAbilities.abilities = charClass.charAbilties;
	}

	void PrintStats(const CharacterTypes& charClass)
	{
		const std::string border = "  ##" + std::string(charClass.Desc.size() + 4, '=') + "##";
		const std::string titlePad((charClass.Desc.size() + 8 - charClass.Name.size()) / 2, ' ');

		GEngine->Print(border, Color::BMagenta, 1);
		GEngine->Print(titlePad + charClass.Name, Color::BMagenta, 1);
		GEngine->Print(border, Color::BMagenta, 2);

		GEngine->Print("    \033[1mDesc: \033[0m" + charClass.Desc, Color::Gray, 2);

		GEngine->Print("    \033[1mHP      : \033[22m" + 
			std::to_string(charClass.Health), Color::Green, 1);
		GEngine->Print("    \033[1mAC      : \033[22m" + 
			std::to_string(charClass.ArmorClass), Color::Green, 1);
		GEngine->Print("    \033[1mStamina : \033[22m" + 
			std::to_string(charClass.Stamina), Color::Green, 2);

		GEngine->Print("    \033[1mAbilties: \033[22m", Color::Green, 0);

		for (int i = 0; i < charClass.charAbilties.size(); i++)
		{
			const CharacterAbility& ability = charClass.charAbilties[i];

			const std::string Effect =
				ability.MinDamage > 0 ? "Damage " + std::to_string(ability.MinDamage) + " - " + std::to_string(ability.MaxDamage) :
				ability.Health > 0 ? "Heals " + std::to_string(ability.Health) :
				ability.Armor > 0 ? "Armor +" + std::to_string(ability.Armor) :
				"No effect";

			GEngine->Print(ability.Name + ": " + Effect, Color::Green, 0);
			GEngine->Print("\n\t\t\033[3m" + ability.Desc + "\033[0m", Color::Gray, 1);
			GEngine->Print("\t      ", Color::Gray, 0);
		}

		GEngine->PrintBlankLines(1);
		GEngine->Print(border, Color::BMagenta, 2);
	}


	// ##===================##
	//			  CREATE NAME
	// ##===================##

	void CreateName(Player& player)
	{

		Dialogue::CharacterCreateDialogue1();

		GEngine->PrintBlankLines(1);
		GEngine->Print("Enter your name...", Color::White, 1);
		GEngine->Print(">> ", Color::White, 0);

		Input::FlushInput();

		std::string inputName;
		getline(std::cin, inputName);
		GEngine->PrintBlankLines(1);

		IsNameValid(inputName, player);

	}

	// ##===================##
	//			  SELECT CLASS
	// ##===================##

	void SelectClass(Player& player)
	{
		GEngine->ClearConsole();
		GEngine->Print("##================================##", Color::BMagenta, 1);
		GEngine->Print("	   Select a Class", Color::BMagenta, 1);
		GEngine->Print("##================================##", Color::BMagenta, 1);

		Dialogue::CharacterCreateDialogue2();

		GEngine->PrintBlankLines(1);
		GEngine->Print("Select A Class from the Options Below: ", Color::White, 1);

		GEngine->TypeOut("1. " + Warlock.Name +
			"\tHealth: " + std::to_string(Warlock.Health) +
			"\tAC: " + std::to_string(Warlock.ArmorClass) +
			"      Mana: " + std::to_string(Warlock.Stamina),
			10ms, 0s, Color::Green, 1);

		GEngine->TypeOut("2. " + Soldier.Name +
			"\tHealth: " + std::to_string(Soldier.Health) +
			"\tAC: " + std::to_string(Soldier.ArmorClass) +
			"      Stamina: " + std::to_string(Soldier.Stamina),
			10ms, 0s, Color::Green, 2);

		Input::FlushInput();

		int ClassSelection = Input::GetInput(">> ", 1, 2);

		if (ClassSelection == 1)
		{
			PrintStats(Warlock);

			GEngine->TypeOut("[BAP] Ready to sign on the dotted line? (Y/N)", 30ms, 0s, Color::Cyan, 1);
			GEngine->Print(">> ", Color::White, 0);

			Input::FlushInput();

			char userChoice;
			std::cin >> userChoice;

			if (userChoice == 'Y' or userChoice == 'y')
			{
				std::cin.ignore();
				GEngine->ClearConsole();
				ApplyClass(player, Warlock);

				Dialogue::CharacterWarlockDialogue1();
			}
			else if (userChoice == 'N' or userChoice == 'n')
			{
				std::cin.ignore();
				GEngine->ClearConsole();
				SelectClass(player);// Recursively restarts name creation if the input is 'N'

			}
			else
			{
				std::cin.ignore();
				GEngine->ErrorMessage("ERROR: Invalid Input! Must be 'Y' or 'N'! ");

				GEngine->ClearConsole();

				SelectClass(player); // Recursively restarts name creation if the input is not 'Y' or 'N'
			}
		}

		else
		{
			GEngine->PrintBlankLines(1);

			PrintStats(Soldier);

			GEngine->TypeOut("[BAP] Are you ready to enlist? (Y/N)", 30ms, 0s, Color::Cyan, 1);
			GEngine->Print(">> ", Color::White, 0);

			char userChoice;
			std::cin >> userChoice;

			if (userChoice == 'Y' or userChoice == 'y')
			{
				std::cin.ignore();
				ApplyClass(player, Soldier);
				GEngine->ClearConsole();

				Dialogue::CharacterSoldierDialogue1();
			}
			else if (userChoice == 'N' or userChoice == 'n')
			{
				std::cin.ignore();
				GEngine->ClearConsole();
				SelectClass(player);// Recursively restarts name creation if the input is 'N'

			}
			else
			{
				std::cin.ignore();
				GEngine->ErrorMessage("ERROR: Invalid Input! Must be 'Y' or 'N'! ");

				GEngine->ClearConsole();

				SelectClass(player); // Recursively restarts name creation if the input is not 'Y' or 'N'
			}
		}
	}

	// Checks if the name is valid and doesn't 
	void IsNameValid(std::string inputName, Player& player)
	{
		if (!inputName.empty())
		{
			for (int i = 0; i < inputName.size(); i++)
			{
				if (isdigit(inputName[i]))
				{
					GEngine->ErrorMessage("ERROR: Your name should not contain any numbers!");

					std::this_thread::sleep_for(2s);
					GEngine->ClearConsole();

					CreateName(player);
					return;
				}
			}

			GEngine->TypeOut("So your name is " + inputName + "? (Y/N)", 30ms, 1s, Color::White, 1);
			GEngine->Print(" >> ", Color::White, 0);

			Input::FlushInput();

			char userChoice;
			std::cin >> userChoice;

			GEngine->PrintBlankLines(1);

			if (userChoice == 'Y' or userChoice == 'y')
			{
				std::cin.ignore();
				player.Name(inputName); // Sets the inputted name to the character's name located in the struct CharacterStats
			}
			else if (userChoice == 'N' or userChoice == 'n')
			{
				std::cin.ignore();
				CreateName(player);// Recursively restarts name creation if the input is 'N'

			}
			else
			{
				std::cin.ignore();
				GEngine->ErrorMessage("ERROR: Invalid Input! Must be 'Y' or 'N'! ");

				GEngine->ClearConsole();

				CreateName(player); // Recursively restarts name creation if the input is not 'Y' or 'N'
			}
		}
		else
		{
			GEngine->ErrorMessage("ERROR: Player name is empty!");
			GEngine->ClearConsole();

			CreateName(player);
		}
	}

	void ShowStats(Player& player)
	{
		GEngine->ClearConsole();
		player.PrintStats();

		system("pause");

	}

	void CreateCharacter(Player& player)
	{
		GEngine->Print("  ##================================##", Color::BMagenta, 1);
		GEngine->Print("             CREATE YOUR HERO", Color::BMagenta, 1);
		GEngine->Print("  ##================================##", Color::BMagenta, 2);
		
		CreateName(player);
		SelectClass(player);
		player.StartingInvetory();
		SaveSystem::SaveGame(player);

		GEngine->ClearConsole();
	}

};

