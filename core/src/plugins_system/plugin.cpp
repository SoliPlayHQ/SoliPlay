#include <plugins_system/plugin.h>
#include <file_system/work_path.h>
#include <tool_functions/path_tools.h>
#include <log_system.h>

// [!!!] 未进行任何测试

namespace SPPlugin {
	Plugin::Plugin(PluginMeta meta) : meta_(meta) {
		handle_ = nullptr;
	}

	Plugin::~Plugin() {
		unloadPlugin();
	}

	void Plugin::loadPlugin(void) {
		// 展开相对路径为绝对路径
		std::filesystem::path pAbsolutePath = std::filesystem::weakly_canonical(meta_.library / meta_.entry_path);

		// 尝试创建插件
		try {
			handle_ = std::make_unique<PluginHandle>(SPTool::PathtoChar(pAbsolutePath));
			SPLog::trace(std::format("Load Plugin {} Success!", meta_.name));

			hookLoad();
		}
		catch (const std::exception& e) {
			throw std::runtime_error(std::format("Plugin {0} Initialize Failed! Cause: {1}",meta_.name,e.what()));
		}
	}

	void Plugin::unloadPlugin(void) {
		handle_.reset();
		SPLog::trace(std::format("Unload Plugin {}!", meta_.name));
	}

	const PluginMeta& Plugin::getMeta(void) {
		return meta_;
	}

	void* Plugin::getFuncAddress(const std::string& strFuncName) {
		return handle_->getFuncAddress(strFuncName);
	}
}
