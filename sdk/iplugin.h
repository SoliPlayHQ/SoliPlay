#pragma once

#ifdef SOLI_PLUGIN_EXPORT
#define SOLIPLAY_API __declspec(dllexport)
#else
#define SOLIPLAY_API __declspec(dllimport)
#endif

typedef void* SOLI_PLUGIN_INSTANCE;

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

extern "C" {
	SOLIPLAY_API void initPlugin(SoliHostAPI hostAPI);
	SOLIPLAY_API SOLI_PLUGIN_INSTANCE createPlugin(void);
	
	SOLIPLAY_API void destroyPlugin(SOLI_PLUGIN_INSTANCE instance);
}
