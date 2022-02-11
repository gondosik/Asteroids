#pragma once
/* Standard (STL) libraries*/
#include <iostream>
#include <fstream>
#include <sstream>

class Logger
{
public:
	/* Methods */
	Logger();
	Logger(std::string);
	~Logger();
	void sendToLog(std::string);
	void sendToLog(const char*);

	void setLogFile(std::string);

	/* Attributes*/
private:
	/* Methods */

	/* Attributes */
	std::ofstream logFile;

};

