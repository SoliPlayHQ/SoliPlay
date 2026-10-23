#include <log_system.h>
#include <iostream>
#include <Windows.h>

/*
简易日志系统（标准控制台终端输入输出）
*/
enum class Level {
	trace = 0,
	debug = 1,
	info = 2,
	warn = 3,
	error = 4,
	fatal = 5
};


Level log_level = Level::trace;

void initLogSystem(Level lv = Level::info) {
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
	log_level = lv;
}

void log(Level lv, std::string msg) {
	if (lv < log_level) return;
	std::cout << msg << std::endl;
}

void trace(std::string msg) {
	log(Level::trace, msg);
}

void debug(std::string msg) {
	log(Level::debug, msg);
}

void info(std::string msg) {
	log(Level::info, msg);
}

void warn(std::string msg) {
	log(Level::warn, msg);
}

void error(std::string msg) {
	log(Level::error, msg);
}

void fatal(std::string msg) {
	log(Level::fatal, msg);
}
