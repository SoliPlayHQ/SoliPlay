#include <file_system/library.h>
#include <file_system/work_path.h>
#include <tool_functions/path_tools.h>
#include <log_system.h>

namespace SPFile {
	std::vector<std::filesystem::path> library;
	std::vector<std::filesystem::path> plugin_library;

	// 初始化库
	void initLibrary(void) {
		// 目前只从可写目录与执行目录获取库，不从其他任何地方获取数据
		std::error_code ec;

		if (std::filesystem::is_directory(getExcutePath() / "core_library", ec))
			library.push_back(getExcutePath() / "core_library");
		else SPLog::error(std::format("Can't Read {0} Failed! Cause: {1}", SPTool::PathtoChar(getExcutePath() / "core_library"), ec.message()));

		if (std::filesystem::is_directory(getExcutePath() / "library", ec))
			library.push_back(getExcutePath() / "library");
		else SPLog::warn(std::format("Can't Read {0} Failed! Cause: {1}", SPTool::PathtoChar(getExcutePath() / "library"), ec.message()));

		if (std::filesystem::is_directory(getWritePath() / "library", ec))
			library.push_back(getWritePath() / "library");
		else SPLog::warn(std::format("Can't Read {0} Failed! Cause: {1}", SPTool::PathtoChar(getWritePath() / "library"), ec.message()));
		
		std::string libraries = "Empty";
		if (!library.empty()) {
			libraries.clear();
			for (auto& path : library) {
				libraries += SPTool::PathtoChar(path) + "\n";
			}
		}

		SPLog::info("Get Library List:\n" + libraries);

		// 检查库内插件文件夹存在性，并建立插件库
		for (auto& path : library) {
			if (std::filesystem::is_directory(path / "plugins", ec))
				plugin_library.push_back(path / "plugins");
			else SPLog::info(std::format("Library {0} does't exist Plugins Library!", SPTool::PathtoChar(path)));
		}

		libraries = "Empty";
		if (!library.empty()) {
			libraries.clear();
			for (auto& path : plugin_library) {
				libraries += SPTool::PathtoChar(path) + "\n";
			}
		}

		SPLog::info("Get Plugins Library List:\n" + libraries);
	}

	const std::vector<std::filesystem::path>& getLibrary(void) {
		return library;
	}

	const std::vector<std::filesystem::path>& getPluginLibrary(void) {
		return plugin_library;
	}
}