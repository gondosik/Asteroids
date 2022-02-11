#include "Logger.h"

Logger::Logger() {
	setLogFile("asteroids.log");
}

Logger::~Logger() {
	logFile.close();
}

Logger::Logger(std::string filename) {
	setLogFile(filename);
}

void Logger::setLogFile(std::string filename) {
	logFile.open(filename.c_str());
}

void Logger::sendToLog(const char* message) {
	logFile << message << std::endl;
}
void Logger::sendToLog(std::string message) {
	logFile << message.c_str() << std::endl;
}