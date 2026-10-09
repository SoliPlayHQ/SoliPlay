#pragma once
#include <string>
#include <vector>

enum class Level {
	TRACE = 0,
	DEBUG = 1,
	INFO = 2,
	WARN = 3,
	ERROR = 4,
	FATAL = 5
};

// 将等级枚举转换为字符串
std::string transLevelToString(Level lv);
// 将字符串转换为等级枚举
Level transLevelToString(std::string strLv);

// 日志记录器
class Logger {
public:
	Logger(std::string name, Level lv, std::vector<LogOutputterBase*>& outputters);

	void trace(const std::string& msg);
	void debug(const std::string& msg);
	void info(const std::string& msg);
	void warn(const std::string& msg);
	void error(const std::string& msg);
	void fatal(const std::string& msg);

	std::string getName(void);
private:
	Level _level;
	std::string _name;
	std::vector<LogOutputterBase*> _outputters;

	void log(Level lv, const std::string& msg);
};

enum class OutputType {
	console,
	file
};

// 日志输出器
class LogOutputterBase {
public:
	std::string getName(void);
	OutputType getType(void);
	virtual ~LogOutputterBase() = default;
	// 向输出器写入日志
	virtual void write(const std::string& msg) = 0;
	// 清空输出器缓存
	virtual void flush(void) = 0;
private:
	std::string _name;
	OutputType _type;
};

// 终端输出器
class ConsoleOutputter : public LogOutputterBase {

};

// 文件输出器
class FileOutputter : public LogOutputterBase {

};

// 日志管理器，全局单例
class LogManager {
public:
	LogManager();
	~LogManager();

	// 获取实例（全局单例）
	static LogManager& getInstance(void);
	// 获取日志记录器
	Logger* getLogger(std::string name);
private:
	LogOutputterBase* getOutputter(std::string name);
	Logger* createLogger(std::string name, std::vector<std::string> setOutter, Level lv);
	void createConsoleOutputter(std::string name);
	std::string createFileOutputter(std::string name, std::string dir, std::string prefix);

	std::vector<LogOutputterBase*> outputters;
	std::vector<Logger*> loggers;

	Level _lvDefault;
};