#pragma once

typedef struct {
	void (*trace)(const char* msg);
	void (*debug)(const char* msg);
	void (*info)(const char* msg);
	void (*warn)(const char* msg);
	void (*error)(const char* msg);
	void (*fatal)(const char* msg);
} SoliLogAPI;

typedef struct {
	SoliLogAPI log;
} SoliHostAPI;

typedef void* SOLI_PLUGIN_INSTANCE;

// Object 插件入口函数
typedef SOLI_PLUGIN_INSTANCE(*CreateInstanceFunc)(const SoliHostAPI* hostAPI);
typedef void (*DestroyInstanceFunc)(const SOLI_PLUGIN_INSTANCE instance);

// Function 插件入口函数
typedef void (*InitPluginFunc)(const SoliHostAPI* hostAPI);