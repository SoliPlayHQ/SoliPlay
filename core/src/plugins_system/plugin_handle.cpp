#include <plugins_system/plugin_handle.h>
#include <stdexcept>
#include <tool_functions/string_tools.h>

namespace SPPlugin {
	PluginHandle::PluginHandle(std::string path) {
		// 检测 Path 是否为空
		if (path.empty()) {
			throw std::invalid_argument("Plugin Path can't be empty!");
		}

		hPlugin_ = LoadLibraryW(SPTool::ChartoWide(path).c_str());
		// 检测 DLL 是否可用
		if (!hPlugin_) {
			DWORD err = GetLastError();
			throw std::runtime_error("LoadLibrary Failed with error code:" + std::to_string(err));
		}

	}

	void* PluginHandle::getFuncAddress(std::string name) {
		return GetProcAddress((HMODULE)hPlugin_, name.c_str());
	}

	PluginHandle::~PluginHandle() {
		FreeLibrary((HMODULE)hPlugin_);
	}
}
