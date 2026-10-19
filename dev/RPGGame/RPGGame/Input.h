#pragma once
#include <string>
#include <windows.h>
#include "GameEngine.h"

namespace Input
{
	static int GetInput(std::string message, int min, int max)
	{
		while (true)
		{
			GEngine->Print(message, Color::White, 0);
			std::string userChoice;
			getline(std::cin, userChoice);

			if (userChoice.size() != 1)
			{
				GEngine->ErrorMessage("Invalid Option: Your input should only contain one character...");

				GEngine->ClearLastLine(2);

				continue;
			}

			try // tries to see if stoi can convert the userChoice
			{

				int convInput = std::stoi(userChoice);
				if (convInput >= min and convInput <= max)
				{
					return convInput;
				}
				else
				{
					GEngine->ErrorMessage("Invalid Option... Please select one of the options from the options menu.");

					GEngine->ClearLastLine(2);
				}
			}
			catch (const std::exception&) // if stoi cannot convert the userChoice, and tells the user to input a valid choice
			{
				GEngine->ErrorMessage("Invalid Option... Please select one of the options from the options menu.");

				GEngine->ClearLastLine(2);
			}
		}
	}

	inline void FlushInput()
	{
		FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
	}

}