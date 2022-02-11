#pragma once

/* Standard (STL) headers */
#include <string>

/* Game libraries */
#include "Logger.h"

const int WINDOW_POSITION_X = 30;
const int WINDOW_POSITION_Y = 250;
const int WINDOW_WIDTH = 500;
const int WINDOW_HEIGHT = 500;
const int NANO_SECONDS_IN_SECOND = 1000000000;
const int BULLET_MAX_AGE = 60;
const int BULLET_MAX_COUNT = 7;
const int ASTEROID_SPAWN_RATE = 100;
const int MAX_ASTEROIDS_PER_LEVEL = 20;
const int MAX_SIMULTANEUS_ASTEROIDS = 10;
const int MAX_LIVES = 3;
const int MAX_TEXT_OBJECTS = 10;
const int NUMBER_OF_ASTEROID_POINTS = 12;
const int MAX_ASTEROID_SIZE_VARIABLE = 8;
const int MAX_ASTEROID_SIZE_CONSTANT = 15;
const int MAX_ASTEROID_SPEED_VARIABLE = 2;
const int MAX_ASTEROID_SPEED_CONSTANT = 1;
const int SPACESHIP_WIDTH = 10;
const int SPACESHIP_HEIGHT = 13;
const double SPACESHIP_THRUST = 0.49;
const double SPACESHIP_DRAG = 0.83;
const double SPACESHIP_TURN_SPEED = 0.06;	
const double SPACESHIP_ACCELERATION_DECREASE_COEFFICIENT = 0.01;
const double COLLISION_DETECTION_COEFFICIENT = 5.0;
const int SPACESHIP_BULLETS_SPEED = 3;


const std::string WINDOW_TITLE = "Asteroids";
const std::string LOG_FILE = "asteroids.log";
const double WINDOW_FPS = 60.0;

extern Logger logger;

