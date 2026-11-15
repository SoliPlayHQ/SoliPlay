#pragma once
#include <iplugin_struct.h>

namespace SPHost {
	// 初始化 Log API
	void initLogAPI(void);

	// 获取 Log API
	const SoliLogAPI& getLogAPI(void);
}
