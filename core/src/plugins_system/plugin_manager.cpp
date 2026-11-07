#include <plugins_system/plugin_manager.h>

namespace SPPlugin {
	PluginManager& PluginManager::getInstance(void) {
		PluginManager instance;
		return instance;
	}
}
