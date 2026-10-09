#include <log_system.h>
#include <Basic Tools/file_basic_tools.h>
#include <iostream>


LogManager& LogManager::getInstance(void) {
	LogManager _instance;
	return _instance;
}

LogManager::LogManager(void) {
	// 工作目录下的 config
	std::string log_config_path = "./config/log_system/log_config.schema.json";

	nlohmann::json logJson = readAllFileToJson(log_config_path);

	if (logJson.is_null()) {
		std::cerr << "日志配置文件不存在！";
		return;
	}

	bool err = false;
	std::string err_reasoning;

	// 解析日志过滤等级
	Level lv = Level::TRACE;
	if (logJson["level"].is_string()) {
		std::string strLv = logJson["level"];
		if (strLv == "TRACE") lv = Level::TRACE;
		else if (strLv == "DEBUG") lv = Level::DEBUG;
		else if (strLv == "INFO") lv = Level::INFO;
		else if (strLv == "WARN") lv = Level::WARN;
		else if (strLv == "ERROR") lv = Level::ERROR;
		else if (strLv == "FATAL") lv = Level::FATAL;
		else {
			// 解析失败报错
			std::cerr << "日志配置文件解析失败！原因：level 字段不符合枚举规范！";
			err = true;
		}
	}
	
	// 解析 Outputter
	if (logJson["outputter"].is_array()) {
		for (const auto& outputter : logJson["outputter"]) {
			if (outputter["name"].is_string()) {
				if (outputter["type"] == "console") createConsoleOutputter(outputter["name"]);
				else if (outputter["type"] == "file") {
					if (outputter["dir"].is_string() && outputter["prefix"].is_string()) {
						if ((err_reasoning = createFileOutputter(outputter["name"], outputter["dir"], outputter["prefix"])) != "[SUCCESS]") {
							std::cerr << "日志配置文件解析失败！原因：" + err_reasoning;
							err = true;
							break;
						}
					}
					else {
						std::cerr << "日志配置文件解析失败！原因：outputter 的 dir 值或 prefix 值不是字符串！";
						err = true;
						break;
					}
				}
				else {
					std::cerr << "日志配置文件解析失败！原因：outputter 的 type 字段不符合枚举规范！";
					err = true;
					break;
				}
			}
			else {
				std::cerr << "日志配置文件解析失败！原因：outputter 的 name 值不是字符串！";
				err = true;
				break;
			}
		}
	}
	else {
		std::cerr << "日志配置文件解析失败！原因：不存在 outputter 字段或字段类型错误！";
		err = true;
	}

	// 解析 Logger
	if (logJson["logger"].is_array()) {
		for (const auto& logger : logJson["logger"]) {
			if (!logger["name"].is_string()) {
				std::cerr << "日志配置文件解析失败！原因：logger 的 name 值不是字符串！";
				err = true;
				break;
			}

			std::vector<std::string> outputters;
			for (const auto& outputter : logJson["logger"]["outputters"]) {
				if (outputter.is_string()) outputters.push_back(outputter);
				else {
					std::cerr << "日志配置文件解析失败！原因：logger 字段中，" << logger["name"] << "的 outputter 字段不为字符串！";
					err = true;
					break;
				}
			}

			createLogger(logger["name"], outputters, lv);

			if (err) break;
		}
	}
}

Logger* LogManager::getLogger(std::string name) {
	for (auto& logger : loggers)
		if (logger->getName() == name)
			return logger;
	return nullptr;
}

Logger* LogManager::createLogger(std::string name, std::vector<std::string> setOutter, Level lv) {
	std::vector<LogOutputterBase*> opts;
	LogOutputterBase* p;
	for (auto& outputter_name : setOutter)
		if ((p = getOutputter(outputter_name)) != nullptr) opts.push_back(p);
		else return;
	Logger* nexLogger = new Logger(name, lv, opts);

	if (nexLogger != nullptr) {
		loggers.push_back(nexLogger);
	}
	
	return nexLogger;
}
