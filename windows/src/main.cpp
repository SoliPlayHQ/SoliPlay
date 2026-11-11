#include <iostream>
#include <log_system.h>
#include <file_system/work_path.h>
#include <plugins_system/plugin_handle.h>
#include <iplugin_struct.h>
#include <file_system/library.h>
#include <plugins_system/plugin_manager.h>

void initSystem(void) {
	SPLog::initLogSystem(SPLog::Level::trace);
	SPFile::initWorkPath();
	SPFile::initLibrary();
	SPPlugin::PluginManager::getInstance().initialize();
}

void shutdownSystem(void) {
	SPPlugin::PluginManager::getInstance().shutdown();
}

int main(void) {
	initSystem();
	shutdownSystem();
	return 0;
}
