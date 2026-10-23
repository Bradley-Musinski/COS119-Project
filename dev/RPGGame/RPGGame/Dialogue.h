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
		"[Narrator] \x1b[3mYou wake up in a patch of grass on the side of the road.\x1b[23m",
		"[Narrator] \x1b[3mYou have no memory of how you got here or even where here is.\x1b[23m",
		"[Narrator] \x1b[3mThe first thing you do is look around to take in your surroundings.\x1b[23m",
		"[Narrator] \x1b[3mYou don't see much of worth while, until you see smoke rising in the distance.\x1b[23m",
		"[You] Huh? Wait... I see smoke! It could be a sign of civilization!"
	};
}

namespace CharacterCreator
{
	inline constexpr  std::array<std::string_view, 6> Lines1 =
	{
		"[Narrator] The door creaks open and the chatter dies down as every eye turns to you...",
		"[Innkeeper] Ah, a new face! Come in, come in! Don't be shy!",
		"[Innkeeper] Welcome to The Last Ember.",
		"[Innkeeper] My name is Godwin. I'm the owner of this inn.",
		"[Narrator] Godwin yells to one of his staff to bring you a drink.",
		"[Godwin] So tell me. What's your name friend?",
	};

	inline constexpr std::array<std::string_view, 6> Lines2 =
	{
		"[Godwin] Ah, what a fitting name for a legend!",
		"[Narrator] A barmaid sets a frothy mug in front of you.",
		"[Godwin] So tell me, what brings you to The Last Ember?",
		"[Godwin] Hmmm...",
		"[Godwin] You don't look like a farmer. So what's your trade?",
		"[Godwin] Are you handy with a blade, a bow, or perhaps... magic?"
	};

	inline constexpr std::array<std::string_view, 3> SoliderLines =
	{
		"[Godwin] Oh, you're a solider?",
		"[Narrator] Godwin chuckles...",
		"[Godwin] Well, nothing beats a good sword and a steady arm!"
	};

	inline constexpr std::array<std::string_view, 3> WarlockLines =
	{
		"[Godwin] Oh, you're a warlock?",
		"[Narrator] Godwin's eyes light up with curiosity...",
		"[Godwin] Well, a little magic never hurt anyone. Glad to have you around!"
	};

}

namespace Dialogue
{
	void CharacterCreateDialogue1()
	{
		for (const auto& line : CharacterCreator::Lines1)
		{
			GEngine->TypeOut(line, 30ms, 1s, Color::Cyan, 1);
		}
	}

	void CharacterCreateDialogue2()
	{
		for (const auto& line : CharacterCreator::Lines2)
		{
			GEngine->TypeOut(line, 30ms, 1s, Color::Cyan, 1);
		}
	}

	void CharacterSoldierDialogue1()
	{
		for (const auto& line : CharacterCreator::SoliderLines)
		{
			GEngine->TypeOut(line, 30ms, 1s, Color::Cyan, 1);
		}
	}
	void CharacterWarlockDialogue1()
	{
		for (const auto& line : CharacterCreator::WarlockLines)
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

