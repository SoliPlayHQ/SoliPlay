#pragma once
#include "iplugin_struct.h"

#ifdef SOLI_PLUGIN_EXPORT
#define SOLIPLAY_API __declspec(dllexport)
#else
#define SOLIPLAY_API __declspec(dllimport)
#endif

// 实例插件基本 API
extern "C" {
	// 初始化插件，提供主程序 Host API
	SOLIPLAY_API void initPlugin(const SoliHostAPI* hostAPI);
}