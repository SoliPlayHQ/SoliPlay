#pragma once
#include <string>
#include <filesystem>
#include <system_error>

namespace SPFile {
	// 从文件读内容，但是会打 warn 级日志
	bool ReadFiletoString(const std::filesystem::path& pathFile, std::string& strOut);
	// 从文件读内容，获取读取失败的错误信息
	bool ReadFiletoString(const std::filesystem::path& pathFile, std::string& strOut, std::error_code& ec);

	// 向文件写内容，但是会打 warn 级日志
	bool WriteStringtoFile(const std::filesystem::path& pathFile, const std::string& strText);
	// 向文件写内容，获取读取失败的错误信息
	bool WriteStringtoFile(const std::filesystem::path& pathFile, const std::string& strText, std::error_code& ec);
}