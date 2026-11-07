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
	SoliLogAPI* log;
} SoliHostAPI;

typedef void* SOLI_PLUGIN_INSTANCE;

typedef void (*InitPluginFunc)(const SoliHostAPI* hostAPI);
typedef SOLI_PLUGIN_INSTANCE (*CreatePluginFunc)(void);
typedef void (*DestroyPluginFunc)(const SOLI_PLUGIN_INSTANCE instance);
