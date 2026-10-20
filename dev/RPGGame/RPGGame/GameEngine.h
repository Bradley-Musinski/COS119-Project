#pragma once
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <memory>
#include <conio.h> // console input/ouput - meant for reading keys directly from the keyboard
#include <windows.h>

using namespace std::chrono_literals;

// Forward declaration so the GameEngine knows that AActor exists
class AActor;

// Forward declares GameEngine so the pointer type is known,
// then declares the global GEngine pointer (defined in GameEngine.cpp) so any class in the program can access it
class GameEngine; 
extern GameEngine* GEngine;

enum class Color
{
	Red,
	Dark_Red,
	Blue,
	Green,
	Yellow,
	Gold,
	Brown,
	Magenta,
	BMagenta,
	Cyan,
	Purple,
	White,
	Gray
};

class GameEngine
{
public:


	GameEngine() = default;
	// Destructor to ensure no memory leaks if the engine closes
	~GameEngine();

	void Run();

/*
* The Manager vs. The Managed conundrum
*
* Question: Who should manage who?
* Instead of having each class worry about deleting itself after being used
*		- Enemy should worry about enemy things
*		- Player should worry about player things
*		- NPC should worry about NPC things
*		- None of these should have to worry about deleting themselves
*
* The class notifies the engine that it has completed its tasks and
* is ready for deletion by using Destroy().
*
* Destroy() flags the object instance with the destruction flag
*
* The engine then removes the object from the heap and frees up that memory address
* Then it purges the pointer from the engine's pointer registry to eliminate any dangling pointers
* (Dangling pointers are pointers that refer to a memory location that has been freed up)
*
* This is a simple deferred-destruction object management system or a simple garbage collection system
* Deferred meaning it will delete this object when it is safe, instead of immediately
*
*/

	void ProcessDeferredDestruction();

	// Registers a new actor into the engine
	void RegisterActor(AActor* actor);

	bool IsRunning() const { return bIsRunning; }
	void RequesetQuit() { bIsRunning = false; }

	void PrintBlankLines(int numOfBlankLines);
	template <typename T> void Print(const T& message, Color color = Color::White, int numOfBlankLines = 0);
	template <typename T> void TypeOut(const T& message, std::chrono::milliseconds delayMs, std::chrono::milliseconds, Color color = Color::White, int BlankLines = 0);
	void ErrorMessage(std::string message);
	void ClearLastLine(int LineAmt);

	void WaitForKey();
	void ClearConsole();



private:
	// The master list of every actor that is currently alive
	std::vector<AActor*> ActorRegistry;

	bool bIsRunning;
};

template<typename T>
inline void GameEngine::Print(const T& message, Color color, int numOfBlankLines)
{
	// 1. Sets the console color based on the enum
	switch (color)
	{
	case Color::Red:     
		std::cout << "\033[31m"; 
		break;
	case Color::Dark_Red:
		std::cout << "\033[36m";
		break;
	case Color::Green:   
		std::cout << "\033[32m"; 
		break;
	case Color::Yellow:  
		std::cout << "\033[33m"; 
		break;
	case Color::Gold:
		std::cout << "\033[1;38;5;220m";
		break;
	case Color::Blue:    
		std::cout << "\033[34m"; 
		break;
	case Color::Magenta: 
		std::cout << "\033[35m"; 
		break;
	case Color::BMagenta:
		std::cout << "\033[95m";
		break;
	case Color::Cyan:    
		std::cout << "\033[36m"; 
		break;
	case Color::White:
		std::cout << "\033[0m";
		break;
	case Color::Gray:
		std::cout << "\033[90m";
		break;
	default:             
		std::cout << "\033[0m";  
		break; // Default white/reset
	}

	std::cout << message; // Prints the actual message that was inputed

	std::cout << "\033[0m"; // Resets the color back to the normal (white) so future prints won't have the same color

	PrintBlankLines(numOfBlankLines); // Prints the requested blank lines
}

template<typename T>
inline void GameEngine::TypeOut(const T& message, std::chrono::milliseconds delayMs, std::chrono::milliseconds delayLine, Color color, int BlankLines)
{
	bool skip = false;

	for (char c : message)
	{

		// If user hits enter it will print the rest of the message instantly
		if (!skip && _kbhit()) // checks to see the the key has been pressed
		{
			if (_getch() == 13) // Reads only one keey right away, without needing enter and without showing it on screen
			{
				skip = true;
			}
		}

		if (skip)
		{
			Print(c, color, 0);
			continue;
		}

		Print(c, color, 0);
		std::cout << std::flush;
		std::this_thread::sleep_for((delayMs));


	}


	std::this_thread::sleep_for((delayLine));
	PrintBlankLines(BlankLines);
}
