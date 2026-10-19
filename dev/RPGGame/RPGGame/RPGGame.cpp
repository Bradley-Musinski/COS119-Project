#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "GameEngine.h"

int main()
{

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetBreakAlloc(-1);

	GameEngine engine;
	GEngine = &engine;

	// Calls the Run() method in the GameEngine.h
	engine.Run();

	GEngine = nullptr;
	return 0;
}
