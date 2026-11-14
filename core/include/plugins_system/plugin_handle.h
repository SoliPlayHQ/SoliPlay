#pragma once
#include <string>
#include <filesystem>

namespace SPPlugin {
	class PluginHandle {
	public:
		explicit PluginHandle(const std::filesystem::path& path);
		~PluginHandle();

		void* getFuncAddress(const std::string& name);

		PluginHandle(const PluginHandle&) = delete;
		PluginHandle& operator=(const PluginHandle&) = delete;
		PluginHandle(PluginHandle&& other) noexcept;
		PluginHandle& operator=(PluginHandle&& other) noexcept;

	private:
		void* hPlugin_;
	};
}
