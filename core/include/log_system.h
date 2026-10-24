#pragma once
#include <string>
#include <source_location>

namespace SPLog {
	enum class Level {
		trace = 0,
		debug = 1,
		info = 2,
		warn = 3,
		error = 4,
		fatal = 5
	};

	void initLogSystem(Level lv);

	void trace(std::string msg, const std::source_location& location = std::source_location::current());
	void debug(std::string msg, const std::source_location& location = std::source_location::current());
	void info(std::string msg, const std::source_location& location = std::source_location::current());
	void warn(std::string msg, const std::source_location& location = std::source_location::current());
	void error(std::string msg, const std::source_location& location = std::source_location::current());
	void fatal(std::string msg, const std::source_location& location = std::source_location::current());
}
