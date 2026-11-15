#pragma once
#include <plugins_system/plugin_type/object_plugin/free_plugin.h>

namespace SPPlugin {
	FreeObjectPlugin::FreeObjectPlugin(PluginMeta meta) : ObjectPlugin(meta) {

	}

	void FreeObjectPlugin::hookObjectLoad(void) {
		return;
	}

	void FreeObjectPlugin::hookObjectUnload(void) {
		return;
	}
}
