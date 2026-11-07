#pragma once
#include <string>

namespace SPTool {
	// char转宽字符
	std::wstring ChartoWide(const std::string& utf8);

	// 宽字符转char
	std::string WidetoChar(const std::wstring& wstr);
}