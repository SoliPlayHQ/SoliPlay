#include <plugins_system/plugin.h>
#include <file_system/work_path.h>
#include <tool_functions/path_tools.h>

// [!!!] 未进行任何测试

namespace SPPlugin {
	Plugin::Plugin(PluginMeta meta) : meta_(meta) {
		handle_ = nullptr;
	}

	void Plugin::loadPlugin(void) {
		// 展开相对路径为绝对路径
		std::filesystem::path pAbsolutePath = std::filesystem::weakly_canonical(meta_.library / meta_.entry_path);

		// 尝试创建插件
		try {
			handle_ = std::make_unique<PluginHandle>(SPTool::PathtoChar(pAbsolutePath));
		}
		catch (const std::exception& e) {
			throw std::runtime_error(std::format("Plugin {0} Initialize Failed! Cause: {1}",meta_.name,e.what()));
		}
	}

	void Plugin::unloadPlugin(void) {
		handle_.reset();
	}
}
