#include <file_system/file_io.h>
#include <iostream>
#include <fstream>

#include <log_system.h>
#include <tool_functions/path_tools.h>

// [!!!] 未进行任何测试

namespace SPFile {
	// 从文件读内容，但是会打 warn 级日志
	bool ReadFiletoString(const std::filesystem::path& pathFile, std::string& strText) {
		std::error_code ec;

		if (ReadFiletoString(pathFile, strText, ec)) return true;
		
		// 打日志
		SPLog::warn(std::format("Can't Read {0}! Cause: {1}", SPTool::PathtoChar(pathFile), ec.message()));
		return false;
	}

	// 从文件读内容，获取读取失败的错误信息
	bool ReadFiletoString(const std::filesystem::path& pathFile, std::string& strText, std::error_code& ec) {
		ec.clear();
		// 读文件大小
		uintmax_t file_size = std::filesystem::file_size(pathFile, ec);
		if (ec) return false;
		if (!file_size) {
			strText.clear();
			return false;
		}

		// 读文件
		std::ifstream ifsFile(pathFile, std::ios::binary);
		if (!ifsFile.is_open()) {
			ec = std::make_error_code(std::errc::permission_denied);
			return false;
		}

		strText.resize(file_size);
		if (ifsFile.read(strText.data(), file_size)) return true;

		ec = std::make_error_code(std::errc::io_error);
		return false;
	}

	// 向文件写内容，但是会打 warn 级日志
	bool WriteStringtoFile(const std::filesystem::path& pathFile, const std::string& strOut) {
		std::error_code ec;

		if (WriteStringtoFile(pathFile, strOut, ec)) return true;

		// 打日志
		SPLog::warn(std::format("Can't Write {0}! Cause: {1}", SPTool::PathtoChar(pathFile), ec.message()));
		return false;
	}

	// 向文件写内容，获取读取失败的错误信息
	bool WriteStringtoFile(const std::filesystem::path& pathFile, const std::string& strOut, std::error_code& ec) {
		// 写入临时文件
		std::filesystem::path pathTemp = pathFile;
		pathTemp += ".tmp";

		{
			std::ofstream ofsFile(pathTemp, std::ios::binary | std::ios::trunc);
			if (!ofsFile.is_open()) return false;

			ofsFile.write(strOut.data(), strOut.size());
			ofsFile.flush();

			if (!ofsFile.good()) return false;
		}

		std::filesystem::rename(pathTemp, pathFile, ec);

		if (ec) {
			std::error_code tec;
			std::filesystem::remove(pathTemp, tec);
			return false;
		}

		return true;
	}
}