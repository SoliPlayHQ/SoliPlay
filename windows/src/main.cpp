#include <iostream>
#include <log_system.h>

int main(void) {
	SPLog::initLogSystem(SPLog::Level::debug);

	SPLog::trace("trace 消息");
	SPLog::debug("debug 消息");
	SPLog::info("info 消息");
	SPLog::warn("warn 消息");
	SPLog::error("error 消息");
	SPLog::fatal("fatal 消息");

	return 0;
}
