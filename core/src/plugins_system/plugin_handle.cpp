#include <plugins_system/plugin_handle.h>
#include <stdexcept>
#include <Windows.h>
#include <tool_functions/string_tools.h>

// [?] 只进行过部分实机可行性测试、单元测试

namespace SPPlugin {
	PluginHandle::PluginHandle(const std::filesystem::path& path) {
		// 检测 Path 是否为空
		if (path.empty()) {
			throw std::invalid_argument("Plugin Path can't be empty!");
		}

		hPlugin_ = LoadLibraryW(path.wstring().c_str());
		// 检测 DLL 是否可用
		if (!hPlugin_) {
			DWORD err = GetLastError();
			throw std::runtime_error("LoadLibrary Failed with error code:" + std::to_string(err));
		}

	}

	void* PluginHandle::getFuncAddress(const std::string& name) {
		return GetProcAddress((HMODULE)hPlugin_, name.c_str());
	}

	PluginHandle::~PluginHandle() {
		FreeLibrary((HMODULE)hPlugin_);
	}
}
