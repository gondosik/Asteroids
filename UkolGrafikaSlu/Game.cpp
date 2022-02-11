/* Standard (STL) headers */
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include <exception>
#include <fstream>
#include <iostream>

/* SDL headers */
#include "SDL.h"
#include "SDL_timer.h"
#include "SDL_ttf.h"

/* Game headers */
#include "Asteroid.h"
#include "Commons.h"
#include "InputManager.h"
#include "Renderer.h"
#include "Spaceship.h"
#include "TextRenderer.h"

#define _USE_MATH_DEFINES

Logger logger(LOG_FILE);

/* ToDo:
	Menu
*/

void gameReset(int& asteroids_level_count) {
	asteroids_level_count = 0;
}
void fullGameReset(int& lives, int& score, int& asteroids_level_count) {
	lives = MAX_LIVES;
	score = 0;
	asteroids_level_count = 0;
}

int main(int argc, char** args) {
	SDL_Surface* winSurface = nullptr;
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_Rect rect[MAX_TEXT_OBJECTS];
	SDL_Texture *texture[MAX_TEXT_OBJECTS];

	/* Menu structures */
	SDL_Rect mainRct;
	mainRct.x = 0;
	mainRct.y = 0;
	mainRct.h = WINDOW_HEIGHT;
	mainRct.w = WINDOW_WIDTH;

	for (auto z = 0; z < MAX_TEXT_OBJECTS; z++) {
		texture[z] = nullptr;
	}

	button_t start_button;
	start_button.colour.r = 255;
	start_button.colour.g = 255;
	start_button.colour.b = 255;
	start_button.colour.a = 255;
	start_button.draw_rect.x = 128;
	start_button.draw_rect.y = 128;
	start_button.draw_rect.w = 128;
	start_button.draw_rect.h = 128;

	enum {
		STATE_IN_MENU,
		STATE_IN_GAME,
	} state = STATE_IN_MENU;

	/* General structures and variables */
	char font_path[] = "FreeSans.ttf";
	bool close_request = false;
	bool info_request = false;
	int frames = 0;
	int updates = 0;
	int score = 0;
	int level = 1;
	int lives = MAX_LIVES;
	int asteroids_level_count = 0;
	srand(time(0));

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
		logger.sendToLog("CHYBA: Nepodarilo se inicializovat SDL: " + std::string(SDL_GetError()));
		return 1;
	}

	SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer);

	winSurface = SDL_GetWindowSurface(window);
	
	if (!window)
	{
		logger.sendToLog("CHYBA: Nepodarilo se vytvorit SDL okno: " + std::string(SDL_GetError()));
		SDL_Quit();
		return 1;
	}
	if (!renderer)
	{
		logger.sendToLog("CHYBA: Nepodarilo se vytvorit SDL renderer: " + std::string(SDL_GetError()));
		SDL_Quit();
		return 1;
	}

	if (!winSurface) {
		logger.sendToLog("CHYBA: Nepodarilo se ziskat vykreslovaci oblast: " + std::string(SDL_GetError()));
		SDL_Quit();
		return 1;
	}
	/* Window parameters setting */
	SDL_SetWindowTitle(window, WINDOW_TITLE.c_str());
	SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
	SDL_RenderClear(renderer);
	TTF_Init();

    TTF_Font *bigFont = TTF_OpenFont(font_path, 20);
	TTF_Font *smallFont = TTF_OpenFont(font_path, 14);

    if (bigFont == NULL) {
		logger.sendToLog("CHYBA: Font nenalezen!");
		SDL_Quit();
		return 1;
	}
	if (smallFont == NULL) {
		logger.sendToLog("CHYBA: Font nenalezen!");
		SDL_Quit();
		return 1;
	}


	logger.sendToLog("INFO: Parametry vykreslovaciho okna jsou:");
	logger.sendToLog("Sirka: " + std::to_string(WINDOW_WIDTH));
	logger.sendToLog("Vyska: " + std::to_string(WINDOW_HEIGHT));
	
	Renderer::init(renderer, WINDOW_WIDTH, WINDOW_HEIGHT);
	InputManager* im = InputManager::getInstance();

	/* Time variables */
	std::chrono::steady_clock::time_point lastTime = std::chrono::steady_clock::now();
	std::chrono::steady_clock::time_point timer = std::chrono::steady_clock::now();
	double ns = NANO_SECONDS_IN_SECOND / WINDOW_FPS;
	double delta = 0;
	/* Basic game variables */
	Spaceship* player = new Spaceship(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, SPACESHIP_WIDTH, SPACESHIP_HEIGHT);
	std::vector<Asteroid*> asteroids;

	while (!close_request)
	{
		try {
			std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now(); /*nano time*/
			delta += (now - lastTime).count() / ns;
			lastTime = now;
			while (delta >= 1)
			{
				/* Input getter */
				im->pollEvents();
				/* Scan for SDL_QUIT or ESC/Q pressing*/
				if (im->getKeyState(SDL_SCANCODE_Q) || im->getKeyState(SDL_SCANCODE_ESCAPE) || im->quitEvent()) close_request = true;
				if (lives <= 0) fullGameReset(lives, score, asteroids_level_count);
					/* Asteroid spawn */
					if (updates % ASTEROID_SPAWN_RATE == 0 && asteroids.size() < MAX_SIMULTANEUS_ASTEROIDS && asteroids_level_count < MAX_ASTEROIDS_PER_LEVEL)
					{
						asteroids_level_count++;
						int radius = (rand() % MAX_ASTEROID_SIZE_VARIABLE) + MAX_ASTEROID_SIZE_CONSTANT;
						int x = 0, y = 0;
						int color = 255 - rand() % 128; /* Asteroid will be in shades of grey to white*/

						/* Spawning coord - somewhere in 10 % of size of each screen side */
						switch (rand() % 4) {
						case 0:
							x = rand() % WINDOW_WIDTH;
							y = rand() % WINDOW_HEIGHT / 10;
							break;
						case 1:
							x = WINDOW_WIDTH - (rand() % WINDOW_WIDTH / 10);
							y = rand() % WINDOW_HEIGHT;
							break;
						case 2:
							x = rand() % WINDOW_WIDTH;
							y = WINDOW_HEIGHT - (rand() % WINDOW_HEIGHT / 10);
							break;
						case 3:
							x = rand() % WINDOW_WIDTH / 10;
							y = rand() % WINDOW_HEIGHT;
							break;
						default:
							x = rand() % WINDOW_WIDTH;
							y = rand() % WINDOW_HEIGHT;
							break;
						}
						/* Speed */
						int vel = (rand() % MAX_ASTEROID_SPEED_VARIABLE) + MAX_ASTEROID_SPEED_CONSTANT;
						double angle = (rand() % 360) * (M_PI / 180);
						asteroids.push_back(new Asteroid(x, y, vel * cos(angle), vel * sin(angle), radius, color));
					}

					/* Update objects */
					player->update(&asteroids);

					if (player->getDead())
					{
						lives--;
						gameReset(asteroids_level_count);
						asteroids.clear();
						player->getBullets()->clear();
						player = new Spaceship(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, SPACESHIP_WIDTH, SPACESHIP_HEIGHT);
					}
					for (int i = asteroids.size() - 1; i >= 0; i--)
					{
						(*(asteroids.begin() + i))->update(player->getBullets(), &asteroids);
						if ((*(asteroids.begin() + i))->getDead())
						{
							score += 20;
							asteroids.erase(asteroids.begin() + i);
						}
					}
					if (asteroids_level_count == MAX_ASTEROIDS_PER_LEVEL && asteroids.size() == 0) {
						level++;
						gameReset(asteroids_level_count);
					}
					updates++;
					delta--;
			}

			/* Render all objects */
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			SDL_RenderClear(renderer);
			/* Text areas */
			TextRenderer::getTextAndRect(renderer, 5, 0, "Score: " + std::to_string(score) + " p", bigFont, &texture[0], &rect[0]);
			TextRenderer::getTextAndRect(renderer, 5, rect[0].y + rect[0].h, "Lives: " + std::to_string(lives), bigFont, &texture[1], &rect[1]);
			TextRenderer::getTextAndRect(renderer, 5, rect[1].y + rect[1].h, "Level: " + std::to_string(level), bigFont, &texture[2], &rect[2]);
			TextRenderer::getTextAndRect(renderer, WINDOW_WIDTH - (WINDOW_WIDTH / 1.99), WINDOW_HEIGHT - (WINDOW_HEIGHT / 25), "1 s [1 p], 1 asteroid [20 p], Q/Esc [Quit]", smallFont, &texture[3], &rect[3]);

			SDL_RenderCopy(renderer, texture[0], NULL, &rect[0]);
			SDL_RenderCopy(renderer, texture[1], NULL, &rect[1]);
			SDL_RenderCopy(renderer, texture[2], NULL, &rect[2]);
			SDL_RenderCopy(renderer, texture[3], NULL, &rect[3]);

			if (close_request) {
				if (lives <= 0) {
					TextRenderer::getTextAndRect(renderer, WINDOW_WIDTH / 4, WINDOW_HEIGHT / 2, "Exiting game - out of lives", bigFont, &texture[9], &rect[9]);
				}
				else {
					TextRenderer::getTextAndRect(renderer, WINDOW_WIDTH / 4, WINDOW_HEIGHT / 2, "Exiting game.", bigFont, &texture[9], &rect[9]);
				}
				SDL_RenderCopy(renderer, texture[9], NULL, &rect[9]);
			}

			player->render();
			for (std::vector<Asteroid*>::iterator it = asteroids.begin(); it != asteroids.end(); ++it)
			{
				(*it)->render();
			}
			frames++;
			SDL_RenderPresent(renderer);
			SDL_DestroyTexture(texture[0]);
			SDL_DestroyTexture(texture[1]);
			SDL_DestroyTexture(texture[2]);
			SDL_DestroyTexture(texture[3]);

			if ((std::chrono::steady_clock::now() - timer).count() > 1000)
			{
				timer += std::chrono::milliseconds(1000);
				updates = 0;
				frames = 0;
				score++;

			}
		}
		catch (std::exception& e)
		{
			logger.sendToLog("CHYBA: Typ chyby je " + std::string(e.what()) );
		}
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}