#include <log_system.h>

Logger::Logger(std::string name, Level lv, std::vector<LogOutputterBase*>& outputters) {
	_level = lv;
	_name = name;
	for (auto& outputter : outputters)
		_outputters.push_back(outputter);
}

void Logger::trace(const std::string& msg) {
	if(_level <= Level::TRACE) log(Level::TRACE, msg);
}

void Logger::debug(const std::string& msg) {
	if (_level <= Level::DEBUG) log(Level::DEBUG, msg);
}

void Logger::info(const std::string& msg) {
	if (_level <= Level::INFO) log(Level::INFO, msg);
}

void Logger::warn(const std::string& msg) {
	if (_level <= Level::WARN) log(Level::WARN, msg);
}

void Logger::error(const std::string& msg) {
	if (_level <= Level::ERROR) log(Level::ERROR, msg);
}

void Logger::fatal(const std::string& msg) {
	if (_level <= Level::FATAL) log(Level::FATAL, msg);
}


void Logger::log(Level lv, const std::string& msg) {
	for (auto &outputter : _outputters)
		outputter->write("[" + transLevelToString(lv) + "]" + msg + "[from logger-" + _name + "]");
}

std::string Logger::getName(void) {
	return _name;
}
