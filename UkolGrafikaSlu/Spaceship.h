#pragma once

/* Standard (STL) headers */
#include <cmath>
#include <string>
#include <vector>

/* SDL headers */
#include <libraries/SDL.h>

/* Game headers */
#include "Asteroid.h"
#include "Bullet.h"
#include "Commons.h"
#include "InputManager.h"
#include "Renderer.h"

#define _USE_MATH_DEFINES

class Spaceship
{
public:
	/* Methods */
	Spaceship(double x, double y, int width, int height);
	~Spaceship();
	void update(std::vector<Asteroid*>* asteroids);
	void render();
	std::vector<Bullet*>* getBullets();
	bool getDead();

	/* Attributes */

private:
	/* Methods */

	/* Attributes */
	InputManager* im;
	int width;
	int height;
	bool dead;
	/* Location and motion of spaceship*/
	double posx;
	double posy;
	double velx;
	double vely;
	double accx;
	double accy;
	double angle;
	double turnSpeed;
	double thrust;
	double drag;
	double bulletspd;
	/* Offensive limitage of spaceship */
	int bulletLimit;
	int bulletMaxAge;
	/* Number of spaceship lives */
	int lives;
	/* Bullets */
	std::vector<Bullet*> bullets;
	/* Rendering*/
	SDL_Point nose;
	SDL_Point lwing;
	SDL_Point rwing;
};