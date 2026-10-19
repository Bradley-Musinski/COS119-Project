#pragma once
#include <iomanip>
#include <string>
#include <chrono>
#include <windows.h>   // cursor control
#include <conio.h>     // _kbhit / _getch
#include <thread>
#include "GameEngine.h"

namespace Screens
{
    inline const std::vector<std::string> BannerLines =
    {
        "<=>==================================<=>",
        "||   #--------------------------#    ||",
        "||   |    \033[90mTHE FALLEN KINGDOM\033[0m    \033[31m|    ||",
        "||   #--------------------------#    ||",
        "||                                   ||",
        "|| <::::::::::[]=o  o=[]::::::::::>  ||",
        "||                                   ||",               
        "||      \033[90m ~ A Text Based RPG ~\033[0m       \033[31m ||",
        "<=>==================================<=>",
    };


    inline void DisplayWelcomeMessage()
    {
        for (const std::string& line : BannerLines)
        {
            GEngine->Print("\t\t\t\t\t" + line, Color::Red, 1);
        }
    }


    inline void DisplayCredits()
    {
        GEngine->ClearConsole();

        GEngine->Print(("\t\t\t\t\t======--------------------------======"), Color::Red, 1);
        GEngine->Print("\t\t\t\t\t|==|            CREDITS           |==|", Color::Red, 1);
        GEngine->Print("\t\t\t\t\t======--------------------------======", Color::Red, 1);

        GEngine->Print("\t\t\t\t\t\t   Bradley Musinski", Color::Red, 2);

        GEngine->WaitForKey();
        GEngine->ClearConsole();
    }

    inline void GoodbyeMessage()
    {
        GEngine->Print("\t\t\t\t\t======--------------------------======", Color::Red, 1);
        GEngine->Print("\t\t\t\t\t|==|            GoodBye :)        |==|", Color::Red, 1);
        GEngine->Print("\t\t\t\t\t======--------------------------======", Color::Red, 1);
    }

    inline void MenuOptions()
    {
        GEngine->Print("\t\t\t\t\t\t - 1. New Adventure -", Color::Red, 1);
        GEngine->Print("\t\t\t\t\t\t   - 2. Load Game -", Color::Red, 1);
        GEngine->Print("\t\t\t\t\t\t    - 3. Credits -", Color::Red, 1);
        GEngine->Print("\t\t\t\t\t\t   - 4. Quit Game -", Color::Red, 1);
    }

    inline void BattleOptions()
    {
        GEngine->Print("Select an option:", Color::Green, 1);
        GEngine->Print("- Basic Attack -", Color::White, 1);
        GEngine->Print("- Abilities -", Color::White, 1);
        GEngine->Print("- Items -", Color::White, 1);
    }
} 