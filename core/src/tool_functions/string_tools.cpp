#include <tool_functions/string_tools.h>
#include <Windows.h>

// [O] 已完成实机可行性测试

namespace SPTool {
	std::wstring ChartoWide(const std::string& utf8) {
		if (utf8.empty()) return {};

		int len = MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), -1, nullptr, 0);
		if (len <= 0) return {};
		std::wstring wstr(len, L'\0');
		MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), -1, &wstr[0], len);
		wstr.pop_back();
		return wstr;
	}

	
	std::string WidetoChar(const std::wstring& wstr) {
		if (wstr.empty()) return {};
		int len = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, nullptr, 0, nullptr, nullptr);
		if (len <= 0) return {};
		std::string str(len, '\0');
		WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, &str[0], len, nullptr, nullptr);
		str.pop_back();
		return str;
	}
}