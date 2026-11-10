#pragma once
#include <string>
#include <vector>
#include <memory>
#include <filesystem>

#include <plugins_system/plugin_handle.h>

namespace SPPlugin {
	enum class PluginType {
		object,
		function
	};

	// 插件元数据结构体
	struct PluginMeta {
		std::string name;
		std::string version;
		PluginType type;
		int arch_version;
		std::filesystem::path library;			//来源库
		std::filesystem::path entry_path;			// 原为 entry，此条会被主程序修饰为用户插件文件夹内相对路径
		std::vector<std::string> dependencies;
	};

	// 插件对象
	class Plugin {
	public:
		Plugin(PluginMeta meta);
		~Plugin() = default;

		// 插件加载管理
		void loadPlugin(void);
		void unloadPlugin(void);
	private:
		PluginMeta meta_;
		std::unique_ptr<PluginHandle> handle_ = nullptr;
	};
}
