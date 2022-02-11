#pragma once
/* Standard (STL) headers */
#include <iostream>
#include <iterator>
#include <unordered_map>
#include <utility>

/* STL headers */
#include <libraries/SDL.h>

/* Game headers*/
#include "Commons.h"
#include "TextRenderer.h"

enum keystate
{
	NOTPRESSED,      // 0
	PRESSED,         // 1
	HOLD,            // 2
	RELEASED         // 3
};

class InputManager
{
public:
	/* methods */
	static InputManager* getInstance();
	void pollEvents();
	int getKeyState(Uint32 key);
	bool quitEvent();
	int clean();

	/* attributes */

private:
	/* methods */
	InputManager();
	~InputManager();
	InputManager(const InputManager&);
	InputManager& operator=(const InputManager&);


	/* attributes */
	bool quit = false;
	std::unordered_map<Uint32, int> keymap;
	std::unordered_map<Uint32, int>::iterator kmiter;
	static InputManager* inputManagerInstance;
};