#include "Asteroid.h"

Asteroid::Asteroid(double x, double y, double vx, double vy, double rad, int color)
{
	posx = x;
	posy = y;
	velx = vx;
	vely = vy;
	radius = rad;
	col = color;
	/* Randomize asteroid parameters */
	for (int a = 0; a < NUMBER_OF_ASTEROID_POINTS; a++)
	{
		double angle = a * (2 * M_PI / NUMBER_OF_ASTEROID_POINTS);
		double rad = radius + ((rand() % MAX_ASTEROID_SIZE_VARIABLE));
		points.push_back(std::make_pair(angle, rad));
	}

	dead = false;
}

double Asteroid::getX()
{
	return posx;
}

double Asteroid::getY()
{
	return posy;
}

double Asteroid::getRadius()
{
	return radius;
}

bool Asteroid::getDead()
{
	return dead;
}

void Asteroid::update(std::vector<Bullet*>* bullets, std::vector<Asteroid*>* asteroids)
{
	posx += velx;
	posy += vely;

	/* Screen wrap */
	double border = radius * 2;
	Renderer* r = Renderer::getInstance();

	if (posx < -border)
		posx = r->getWidth() + border;
	else if (posx > r->getWidth() + border)
		posx = -border;

	if (posy < -border)
		posy = r->getHeight() + border;
	else if (posy > r->getHeight() + border)
		posy = -border;

	/* Collision between bullet and asteroid */
	for (std::vector<Bullet*>::iterator it = bullets->begin(); it != bullets->end(); ++it)
	{
		double bx = (*it)->getX();
		double by = (*it)->getY();
		double dx = posx - bx;
		double dy = posy - by;
		if ((dx * dx + dy * dy) <= ((radius * radius) - COLLISION_DETECTION_COEFFICIENT))
		{
			/* If asteroid is large enough, we will create two descendants */
			if (radius > MAX_ASTEROID_SIZE_CONSTANT)
			{
				double nr = radius / 2;
				double nx = posx + ((rand() % 5) - 10);
				double ny = posy + ((rand() % 5) - 10);
				double nv = (rand() % MAX_ASTEROID_SPEED_VARIABLE) + MAX_ASTEROID_SPEED_CONSTANT;
				double na = (rand() % 360) * (M_PI / 180);
				asteroids->push_back(new Asteroid(nx, ny, nv * cos(na), nv * sin(na), nr, col));
				nx = posx + ((rand() % 5) - 2);
				ny = posy + ((rand() % 5) - 2);
				nv = (rand() % MAX_ASTEROID_SPEED_VARIABLE) + MAX_ASTEROID_SPEED_CONSTANT;
				na = (rand() % 360) * (M_PI / 180);
				asteroids->push_back(new Asteroid(nx, ny, nv * cos(na), nv * sin(na), nr, col));
			}
			bullets->erase(it);
			dead = true;
			break;
		}
	}
}

void Asteroid::render()
{
	SDL_Renderer* r = Renderer::getInstance()->getRenderer();
	std::pair<double, double> start = *(points.begin());
	double lastx = -1.0;
	double lasty = -1.0;
	bool first = true;
	SDL_SetRenderDrawColor(r, col, col, col, 255);
	for (std::vector<std::pair<double, double>>::iterator it = points.begin(); it != points.end(); ++it)
	{
		double px = posx + ((*it).second * cos((*it).first));
		double py = posy + ((*it).second * sin((*it).first));
		if (!first)
		{
			SDL_RenderDrawLine(r, (int)px, (int)py, (int)lastx, (int)lasty);
		}
		first = false;
		lastx = px;
		lasty = py;
	}
	double fx = posx + (start.second * cos(start.first));
	double fy = posy + (start.second * sin(start.first));
	SDL_RenderDrawLine(r, (int)lastx, (int)lasty, (int)fx, (int)fy);
}