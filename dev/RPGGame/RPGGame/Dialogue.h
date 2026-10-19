#pragma once
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <vector>
#include <array>
#include <string_view>
#include "GameEngine.h"
#include "Player.h"

namespace IntroLines
{
	inline constexpr std::array<std::string_view, 5> Lines =
	{
		"[Narrator] You wake up in a patch of grass on the side of the road.",
		"[Narrator] You have no memory of how you got here or even where here is.",
		"[Narrator] The first thing you do is look around to take in your surroundings.",
		"[Narrator] You don't see much of worth while, until you see smoke rising in the distance.",
		"[You] Huh? Wait... I see smoke! It could be a sign of civilization!"
	};
}

namespace CharacterCreator
{
	inline constexpr  std::array<std::string_view, 2> Lines1 =
	{
		"[BAP] Hello! Welcome to the Build-A-Player!",
		"[BAP] I will walk you through the process of creating a new character!",
	};

}

namespace Dialogue
{
	void CharacterCreateDialogue()
	{
		for (const auto& line : CharacterCreator::Lines1)
		{
			GEngine->TypeOut(line, 30ms, 1s, Color::Cyan, 1);
		}
	}


	void Intro()
	{

		for (const auto& line : IntroLines::Lines)
		{
			GEngine->TypeOut(line, 30ms, 1s, Color::White, 1);
		}

	}


	void StartDialogue()
	{
		Intro();
	}

};

