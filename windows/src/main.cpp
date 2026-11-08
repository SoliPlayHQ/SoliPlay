#include <iostream>
#include <log_system.h>
#include <file_system/work_path.h>
#include <plugins_system/plugin_handle.h>
#include <iplugin_struct.h>
#include <file_system/library.h>

void InitSystem(void) {
	SPLog::initLogSystem(SPLog::Level::debug);
	SPFile::initWorkPath();
	SPFile::initLibrary();
}

int main(void) {
	InitSystem();

	return 0;
}
