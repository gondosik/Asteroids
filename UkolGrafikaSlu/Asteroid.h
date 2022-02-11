#pragma once

#define _USE_MATH_DEFINES

/* Standard (STL) headers */
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <utility>
#include <vector>

/* Game headers */
#include "Bullet.h"
#include "Commons.h"

class Asteroid
{
public:
	/* Methods */
	Asteroid(double x, double y, double vx, double vy, double rad, int color);
	~Asteroid();
	void update(std::vector<Bullet*>* bullets, std::vector<Asteroid*>* asteroids);
	void render();
	double getX();
	double getY();
	double getRadius();
	bool getDead();

	/* Attributes */

private:
	/* Methods */

	/* Attributes */
	bool dead;
	double posx;
	double posy;
	double velx;
	double vely;
	double radius; // rad angle value
	int col;
	std::vector<std::pair<double, double>> points;

};
