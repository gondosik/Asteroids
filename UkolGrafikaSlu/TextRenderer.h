#pragma once
/* Standard (STL) headers */
#include <cmath>
#include <string>
#include <vector>

/* SDL headers */
#include "libraries/SDL.h"
#include "libraries/SDL_ttf.h"

/* Button structure */
typedef struct {
	SDL_Rect draw_rect;
	struct {
		Uint8 r, g, b, a;
	} colour;

	bool pressed;
} button_t;


class TextRenderer
{
public:
	/* Methods */
	static void getTextAndRect(SDL_Renderer*, int, int, std::string, TTF_Font*, SDL_Texture **, SDL_Rect *);
	static void buttonProcessEvent(button_t*, const SDL_Event*);
	static bool button(SDL_Renderer *, button_t *);
	/* Attributes */
private:
	/* Methods */
	/* Disallow creating an instance of this object */
	TextRenderer() {}
	/* Attributes */

};

