#include <iostream>
#include <log_system.h>
#include <file_system/work_path.h>
#include <plugins_system/plugin_handle.h>
#include <iplugin_struct.h>
#include <file_system/library.h>
#include <plugins_system/plugin_manager.h>
#include <plugins_system/host_api/host_api.h>
#include <plugins_system/plugin_type/object_plugin/free_plugin.h>

void initSystem(void) {
	SPLog::initLogSystem(SPLog::Level::trace);
	SPFile::initWorkPath();
	SPFile::initLibrary();

	SPHost::initHostAPI();
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
