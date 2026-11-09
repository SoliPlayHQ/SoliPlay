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

	const std::string headLevel[] = {"[TRACE]","[DEBUG]","[INFO ]","[WARN ]","[ERROR]","[FATAL]"};

	void initLogSystem(Level lv);

	void trace(const std::string& msg, const std::source_location& location = std::source_location::current());
	void debug(const std::string& msg, const std::source_location& location = std::source_location::current());
	void info(const std::string& msg, const std::source_location& location = std::source_location::current());
	void warn(const std::string& msg, const std::source_location& location = std::source_location::current());
	void error(const std::string& msg, const std::source_location& location = std::source_location::current());
	void fatal(const std::string& msg, const std::source_location& location = std::source_location::current());
}
