#pragma once
#include <string>

void initLogSystem(Level lv);

void trace(std::string msg);
void debug(std::string msg);
void info(std::string msg);
void warn(std::string msg);
void error(std::string msg);
void fatal(std::string msg);