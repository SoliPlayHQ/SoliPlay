#pragma once
#include <plugins_system/plugin.h>
#include <iplugin_struct.h>

namespace SPPlugin {
	// 实例插件，负责实例通用周期管理，自动在卸载前销毁实例。一切子类仅负责附加元数据解析、业务函数映射
	class ObjectPlugin : public Plugin {
	public:
		ObjectPlugin(PluginMeta meta);
		~ObjectPlugin() = default;

		// 创建实例
		SOLI_PLUGIN_INSTANCE createInstance();
		// 销毁实例
		void destroyInstance(SOLI_PLUGIN_INSTANCE instance);
	protected:
		void hookLoad(void) override;
		void hookUnload(void) override;

		virtual void hookObjectLoad(void) = 0;
		virtual void hookObjectUnload(void) = 0;
	private:
		CreateInstanceFunc createInstance_ = nullptr;
		DestroyInstanceFunc destroyInstance_ = nullptr;
	};
}
