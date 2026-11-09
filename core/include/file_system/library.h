#pragma once
#include <string>
#include <vector>
#include <filesystem>

namespace SPFile {
	// 初始化库
	void initLibrary(void);

	// 获取库列表
	const std::vector<std::filesystem::path>& getLibrary(void);
	// 获取存在的库列表
	const std::vector<std::filesystem::path>& getPluginLibrary(void);
}