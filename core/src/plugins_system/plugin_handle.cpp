#include <plugins_system/plugin_handle.h>
#include <stdexcept>

std::wstring ChartoWide(const std::string& utf8) {
	if (utf8.empty()) return {};
	std::string nmstr = utf8;
	for (auto& ch : nmstr)
		if (ch == L'/') ch = L'\\';

	int len = MultiByteToWideChar(CP_UTF8, 0, nmstr.c_str(), -1, nullptr, 0);
	if (len <= 0) return {};
	std::wstring wstr(len, L'\0');
	MultiByteToWideChar(CP_UTF8, 0, nmstr.c_str(), -1, &wstr[0], len);
	wstr.pop_back();
	return wstr;
}


namespace SPPlugin {
	PluginHandle::PluginHandle(std::string path) {
		if (path.empty()) {
			throw std::invalid_argument("Plugin path can't be empty!");
		}

		hPlugin_ = LoadLibraryW(ChartoWide(path).c_str());
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
