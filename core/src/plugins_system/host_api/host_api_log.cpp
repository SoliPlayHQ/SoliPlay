#include <plugins_system/host_api/host_api_log.h>
#include <log_system.h>

namespace SPHost {
	void trace(const char* msg) {
		SPLog::trace(msg);
	}

	void debug(const char* msg) {
		SPLog::debug(msg);
	}

	void info(const char* msg) {
		SPLog::info(msg);
	}

	void warn(const char* msg) {
		SPLog::warn(msg);
	}

	void error(const char* msg) {
		SPLog::error(msg);
	}

	void fatal(const char* msg) {
		SPLog::fatal(msg);
	}

	static SoliLogAPI log_api;

	// 初始化 Log API
	void initLogAPI(void) {
		log_api.trace = trace;
		log_api.debug = debug;
		log_api.info = info;
		log_api.warn = warn;
		log_api.error = error;
		log_api.fatal = fatal;
	}

	// 获取 Log API
	const SoliLogAPI& getLogAPI(void) {
		return log_api;
	}
}