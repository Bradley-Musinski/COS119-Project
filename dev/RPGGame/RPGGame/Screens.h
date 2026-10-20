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
"<>==============================================<>",
        "||                                              ||",
        "||                             \033[1;38;5;196m()\033[0;31m               ||",
        "||                             \033[38;5;136m##\033[0;31m               ||",
        "||                          \033[1;38;5;220m<==##==>\033[0;31m            ||",
        "||  \033[38;5;124m<>-------------------------\033[1;38;5;252m||\033[0;38;5;124m-----------<>\033[0;31m  ||",
        "||  \033[38;5;124m|\033[1;38;5;220m  T H E   F A L L E N   K \033[1;38;5;252m||\033[1;38;5;220m N G D O M \033[0;38;5;124m|\033[0;31m   ||",
        "||  \033[38;5;124m<>-------------------------\033[1;38;5;252m||\033[0;38;5;124m-----------<>\033[0;31m  ||",
        "||                             \033[1;38;5;252m||\033[0;31m               ||",
        "||                             \033[1;38;5;252m||\033[0;31m               ||",
        "||                             \033[1;38;5;252m\\/\033[0;31m               ||",
        "||                                              ||",
        "||             \033[3;90m~ A Text Based RPG ~\033[0;31m             ||",
        "||                                              ||",
        "<>==============================================<>",
    };


    inline void DisplayWelcomeMessage()
    {
        GEngine->PrintBlankLines(4);
        for (const std::string& line : BannerLines)
        {
            GEngine->Print("\t\t\t\t  " + line, Color::Red, 1);
        }
        GEngine->PrintBlankLines(1);
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