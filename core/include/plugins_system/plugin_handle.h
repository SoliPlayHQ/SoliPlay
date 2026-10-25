#pragma once
#include <string>
#include <Windows.h>

namespace SPPlugin {
	class PluginHandle {
	public:
		explicit PluginHandle(std::string path);
		~PluginHandle();

		void* getFuncAddress(std::string name);

		PluginHandle(const PluginHandle&) = delete;
		PluginHandle& operator=(const PluginHandle&) = delete;
		PluginHandle(PluginHandle&& other) noexcept;
		PluginHandle& operator=(PluginHandle&& other) noexcept;

	private:
		void* hPlugin_;
	};
}
