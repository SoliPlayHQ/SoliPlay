#pragma once
#include <iplugin_struct.h>
#include <plugins_system/host_API.h>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

#include <plugins_system/plugin.h>

namespace SPPlugin {
	// 插件管理器
	class PluginManager {
	public:
		static PluginManager& getInstance(void);

		PluginManager() = default;
		~PluginManager() = default;

		// 运行周期管理
		void initialize(void);
		void shutdown(void);

		// 扫描并装配所有插件文件夹下的所有插件
		void loadPlugins(const std::filesystem::path& pathLibrary);

		// 获取插件
		Plugin* getPlugin(const std::string plugin_id);
	private:
		std::unordered_map<std::string, std::unique_ptr<Plugin>> mapPlugins_;
	};
}
