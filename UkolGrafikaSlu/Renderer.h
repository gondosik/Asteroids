#pragma once
/* SDL headers */
#include "libraries/SDL.h"

class Renderer
{
public:
	/* Methods */
	static Renderer* getInstance();
	static Renderer* init(SDL_Renderer* r, int w, int h);
	SDL_Renderer* getRenderer();
	int getWidth();
	int getHeight();

	/* Attributes */

private:
	/* Methods */
	Renderer();
	~Renderer();

	/* Attributes */
	SDL_Renderer* renderer;
	int width;
	int height;
	static Renderer* rendererInstance;
};

