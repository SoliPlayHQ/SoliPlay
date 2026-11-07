#pragma once
#include "iplugin_struct.h"

#ifdef SOLI_PLUGIN_EXPORT
#define SOLIPLAY_API __declspec(dllexport)
#else
#define SOLIPLAY_API __declspec(dllimport)
#endif

// 实例插件基本 API
extern "C" {
	// 初始化插件，提供主程序工具 API
	SOLIPLAY_API void initPlugin(const SoliHostAPI* hostAPI);
	// 创建插件实例
	SOLIPLAY_API SOLI_PLUGIN_INSTANCE createInstance(void);

	// 销毁插件实例
	SOLIPLAY_API void destroyInstance(const SOLI_PLUGIN_INSTANCE instance);
}