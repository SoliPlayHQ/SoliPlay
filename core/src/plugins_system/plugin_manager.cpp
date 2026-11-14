#include <plugins_system/plugin_manager.h>
#include <plugins_system/plugin_type.h>
#include <log_system.h>
#include <tool_functions/path_tools.h>
#include <file_system/library.h>
#include <file_system/file_io.h>

#include <filesystem>
#include <nlohmann/json.hpp>

// [!!!] 未进行任何测试

namespace SPPlugin {
	PluginMeta analyseMeta(std::string strMeta, std::filesystem::path pathLibrary, std::filesystem::path pathParent);

	PluginManager& PluginManager::getInstance(void) {
		static PluginManager instance;
		return instance;
	}

	// 运行周期管理
	void PluginManager::initialize(void) {
		SPLog::info("Plugin Manager Initialize...");
		const std::vector<std::filesystem::path>& plugin_library = SPFile::getPluginLibrary();
		for (auto& path : plugin_library)
			loadPlugins(path);

		SPLog::info(std::format("Plugin Manager Initialize Success! Get {0} Plugins!", mapPlugins_.size()));
	}

	void PluginManager::shutdown(void) {
		for (auto& [key, value] : mapPlugins_)
			value->unloadPlugin();

		mapPlugins_.clear();
	}

	// 扫描并装配指定库中，插件文件夹下的所有插件
	void PluginManager::loadPlugins(const std::filesystem::path& pathLibrary) {
		for (std::filesystem::directory_iterator item(pathLibrary), end; item != end; ++item) {
			if (std::filesystem::is_directory(item->path())) {
				if (std::filesystem::is_regular_file(item->path() / "meta.json")) {
					std::string strMeta;
					SPFile::ReadFiletoString(item->path() / "meta.json", strMeta);
					try {
						PluginMeta meta = analyseMeta(strMeta, pathLibrary, item->path().filename());

						if (mapPlugins_.find(meta.name) == mapPlugins_.end()) {
							if (meta.type == PluginType::object) {
								mapPlugins_.emplace(meta.name, std::make_unique<ObjectPlugin>(meta));
							}
						}
						else {
							SPLog::warn(std::format("Name of Plugin from {0} is Clashes with Plugin from {1}!", SPTool::PathtoChar(item->path()), SPTool::PathtoChar(meta.library / meta.entry_path.parent_path())));
						}
					}
					catch (const std::exception& e) {
						SPLog::warn(std::format("meta.json from Directory {0} analyse Failed! Cause: {1}", SPTool::PathtoChar(item->path()), e.what()));
					}
				}
			}
		}
	}

	// 获取插件对象
	Plugin* PluginManager::getPlugin(const std::string plugin_id) {
		auto item = mapPlugins_.find(plugin_id);
		if (item == mapPlugins_.end())
			throw std::runtime_error(std::format("Plugin {} isn't exist!", plugin_id));
		return item->second.get();
	}


	// 解析 Meta 文件
	PluginMeta analyseMeta(std::string strMeta, std::filesystem::path pathLibrary, std::filesystem::path pathParent) {
		PluginMeta plugin_meta;

		plugin_meta.library = pathLibrary;
		try {
			nlohmann::json jsonMeta = nlohmann::json::parse(strMeta);

			// name 解析
			if (jsonMeta.contains("name") && jsonMeta["name"].is_string()) {
				plugin_meta.name = jsonMeta["name"].get<std::string>();
			}
			else {
				throw std::runtime_error("meta.json missing \"name\" Field or Invalid type(Must be string)");
			}

			// version 解析
			if (jsonMeta.contains("version") && jsonMeta["version"].is_string()) {
				plugin_meta.version = jsonMeta["version"].get<std::string>();
			}
			else {
				throw std::runtime_error("meta.json missing \"version\" field or Invalid type (Must be string)");
			}

			// arch_version 解析
			if (jsonMeta.contains("arch_version") && jsonMeta["arch_version"].is_number_integer()) {
				plugin_meta.arch_version = jsonMeta["arch_version"].get<int>();
			}
			else {
				throw std::runtime_error("meta.json missing \"arch_version\" field or Invalid type (Must be integer)");
			}

			// type 解析
			if (jsonMeta.contains("type") && jsonMeta["type"].is_string()) {
				std::string typeStr = jsonMeta["type"].get<std::string>();
				if (typeStr == "object") {
					plugin_meta.type = PluginType::object;
				}
				else if (typeStr == "function") {
					plugin_meta.type = PluginType::function;
				}
				else {
					throw std::runtime_error("meta.json Type Must Be 'object' Or 'function'");
				}
			}
			else {
				throw std::runtime_error("meta.json missing \"type\" field or Invalid type (Must be string)");
			}

			// entry 解析、修饰相对路径
			if (jsonMeta.contains("entry") && jsonMeta["entry"].is_string()) {
				plugin_meta.entry_path = pathParent / std::filesystem::path(jsonMeta["entry"].get<std::string>());
			}
			else {
				throw std::runtime_error("meta.json missing \"entry\" field or Invalid type (Must be string)");
			}

			// dependencies 解析
			if (jsonMeta.contains("dependencies")) {
				if (jsonMeta["dependencies"].is_array()) {
					for (const auto& item : jsonMeta["dependencies"]) {
						if (item.is_string()) {
							plugin_meta.dependencies.push_back(item.get<std::string>());
						}
						else {
							throw std::runtime_error("meta.json Dependencies Array contains non-string elements");
						}
					}
				}
				else {
					throw std::runtime_error("meta.json \"dependencies\" must be array");
				}
			}

			// debug 报告
			std::string type_str = (plugin_meta.type == PluginType::object) ? "Object (Instance)" : "Function (Tool)";
			std::string deps_str = "None";
			if (!plugin_meta.dependencies.empty()) {
				deps_str = "";
				for (int i = 0; i < plugin_meta.dependencies.size(); ++i) {
					deps_str += plugin_meta.dependencies[i];
					if (i < plugin_meta.dependencies.size() - 1) deps_str += ", ";
				}
			}

			SPLog::debug(std::format(
				"\n================ [{0} Plugin Meta Parsed Successfully] ================\n"
				"  [Name]         : {0}\n"
				"  [Version]      : {1}\n"
				"  [Type]         : {2}\n"
				"  [Arch Version] : {3}\n"
				"  [Entry Path]   : {4}\n"
				"  [Origin]       : {5}\n"
				"  [Dependencies] : {6}\n"
				"=======================================================================",
				plugin_meta.name, plugin_meta.version, type_str,
				plugin_meta.arch_version, SPTool::PathtoChar(plugin_meta.entry_path),
				SPTool::PathtoChar(plugin_meta.library), deps_str
			));

		}
		catch (const nlohmann::json::parse_error& e) {
			throw std::runtime_error("JSON Syntax Parse Failed: " + std::string(e.what()));
		}
		catch (const std::exception& e) {
			throw;
		}

		return plugin_meta;
	}
}
