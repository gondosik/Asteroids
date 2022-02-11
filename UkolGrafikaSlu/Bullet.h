#pragma once

/* SDL headers */
#include <SDL.h>

/* Game headers */
#include "Commons.h"
#include "Renderer.h"

class Bullet
{
public:
	/* Methods */
	Bullet(double x, double y, double vx, double vy, double a, int l);
	~Bullet();
	void update();
	void render();
	double getX();
	double getY();
	double getA();


	/* Attributes */

private:
	/* Methods */
	
	/* Attributes */
	double posx;
	double posy;
	double velx;
	double vely;
	int age;
	double angle; // rad angle value
};


