#pragma once
#include <iplugin_struct.h>

namespace SPHost {
	// 初始化 Host API
	void initHostAPI(void);

	// 获取 Host API
	const SoliHostAPI& getHostAPI(void);
}