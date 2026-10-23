#pragma once
#include <iostream>
#include <conio.h>
#include <string>
#include "Screens.h"
#include "Input.h"

/*
* Namespace menus is a UI Helper layer. 
* It keeps the code separate from the engine logic
* 
*/

namespace Menus
{

    // Main Menu 
    inline int MainMenu()
    {
        bool bIsLooping = true;


        Screens::DisplayWelcomeMessage();

        GEngine->Print("\t\t\t\t\t\t\033[5mPress ENTER to continue...", Color::Red, 1);

        while (bIsLooping)
        {
            if (_getch() == 13)
            {
                GEngine->ClearLastLine(1);
                Screens::MenuOptions();

                int MenuChoice = Input::GetInput("\t\t\t\t\t\t\t >> ", 1, 4);

                switch (MenuChoice)
                {
                case 1:
                    GEngine->ClearConsole();
                    break;

                case 2:
                    GEngine->ClearConsole();
                    break;

                case 3:
                    GEngine->ClearConsole();
                    Screens::DisplayCredits();
                    break;
                case 4:
                    GEngine->ClearConsole();
                    Screens::GoodbyeMessage();
                    bIsLooping = false;

                    break;

                default:
                    GEngine->Print("ERROR: Invalid Choice...", Color::Red, 1);
                    GEngine->ClearConsole();
                    break;
                }

                return MenuChoice;

            }
        }
    }

    inline int BattleOptionsMenu()
    {
        Screens::BattleOptions();

        int userChoice = Input::GetInput(">> ", 1, 4);

        switch (userChoice)
        {
        case 1: // Basic Attack
            break;
        case 2: // Abilities
            break;
        case 3: // Items
            break;
        case 4: // Flee
            GEngine->ClearConsole();
            break;
        default:
            break;
        }

        return userChoice;

    }

}
