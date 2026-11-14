#pragma once
#include <plugins_system/plugin.h>
#include <plugins_system/host_API.h>

namespace SPPlugin {
	class ObjectPlugin : public Plugin {
	public:
		ObjectPlugin(PluginMeta meta);
		~ObjectPlugin() = default;

		// 创建实例
		SOLI_PLUGIN_INSTANCE createInstance();
		// 销毁实例
		void destroyInstance(SOLI_PLUGIN_INSTANCE instance);
	protected:
		void hookLoad(void);
		void hookUnload(void);

		virtual void hookObjectLoad(void) = 0;
		virtual void hookObjectUnload(void) = 0;
	private:
		CreateInstanceFunc createInstance_ = nullptr;
		DestroyInstanceFunc destroyInstance_ = nullptr;
	};
}
