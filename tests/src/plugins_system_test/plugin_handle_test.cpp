#include "pch.h"
#include <plugins_system/plugin_handle.h>
#include "..\core\src\plugins_system\plugin_handle.cpp"

/*
PluginHandle 单元测试
*/

TEST(PluginHandleTest, LoadValidDLL) {
	SPPlugin::PluginHandle handle("kernel32.dll");
	EXPECT_NE(handle.getFuncAddress("GetLastError"), nullptr);
}

TEST(PluginHandleTest, LoadInvalidDLLThrow) {
	EXPECT_THROW({
		SPPlugin::PluginHandle handle("NoExistThisDLL.dll");
	  }, std::runtime_error);
}

TEST(PluginHandleTest, getInvalidFunc) {
	SPPlugin::PluginHandle handle("kernel32.dll");
	void* pFunc = handle.getFuncAddress("NotExistFunc123");
	EXPECT_EQ(pFunc, nullptr);
}