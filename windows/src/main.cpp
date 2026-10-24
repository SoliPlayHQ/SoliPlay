#include <iostream>
#include <log_system.h>

int main(void) {
	Log::initLogSystem(Log::Level::debug);

	Log::trace("trace 消息");
	Log::debug("debug 消息");
	Log::info("info 消息");
	Log::warn("warn 消息");
	Log::error("error 消息");
	Log::fatal("fatal 消息");

	return 0;
}
