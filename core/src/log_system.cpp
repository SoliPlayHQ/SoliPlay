#include <log_system.h>
#include <iostream>
#include <Windows.h>
/*
简易日志系统（标准控制台终端输入输出）
*/
namespace SPLog {
	std::string get_filename(const char* path) {
		const char* p = path + std::strlen(path);
		while ((p > path) && (*(p - 1) != '\\' && *(p - 1) != '/'))
			--p;

		return p;
	}

	Level log_level = Level::trace;

	void initLogSystem(Level lv = Level::info) {
		SetConsoleOutputCP(CP_UTF8);
		SetConsoleCP(CP_UTF8);
		log_level = lv;
	}

	void log(Level lv, std::string msg, const std::source_location& location) {
		if (lv < log_level) return;
		std::cout << get_filename(location.file_name()) << ':' << location.line() << " - " << msg << std::endl;
	}

	void trace(std::string msg, const std::source_location& location) {
		log(Level::trace, msg, location);
	}

	void debug(std::string msg, const std::source_location& location) {
		log(Level::debug, msg, location);
	}

	void info(std::string msg, const std::source_location& location) {
		log(Level::info, msg, location);
	}

	void warn(std::string msg, const std::source_location& location) {
		log(Level::warn, msg, location);
	}

	void error(std::string msg, const std::source_location& location) {
		log(Level::error, msg, location);
	}

	void fatal(std::string msg, const std::source_location& location) {
		log(Level::fatal, msg, location);
	}

}
