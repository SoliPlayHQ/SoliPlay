#pragma once
#include <plugins_system/plugin_type/plugin_type.h>

namespace SPPlugin {
	class FreeObjectPlugin : public ObjectPlugin {
	public:
		FreeObjectPlugin(PluginMeta meta);
		~FreeObjectPlugin() = default;
	protected:
		void hookObjectLoad(void) override;
		void hookObjectUnload(void) override;
	};
}
