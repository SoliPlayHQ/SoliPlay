#include <plugins_system/plugin_manager.h>
#include <log_system.h>
#include <tool_functions/path_tools.h>

#include <filesystem>
#include <nlohmann/json.hpp>

namespace SPPlugin {
	PluginManager& PluginManager::getInstance(void) {
		PluginManager instance;
		return instance;
	}

	// 运行周期管理
	void PluginManager::initialize(void) {

	}

	void PluginManager::shutdown(void) {
		for (auto& [key, value] : mapPlugins)
			value->unloadPlugin();

		mapPlugins.clear();
	}

	// 扫描并装配所有插件文件夹下的所有插件
	//void PluginManager::loadPlugins(void);

	/*
	// 插件元数据结构体
	struct PluginMeta {
		std::string name;
		std::string version;
		PluginType type;
		int arch_version;
		std::string origin;			//来源库
		std::string entry_path;			// 原为 entry，此条会被主程序修饰为用户插件文件夹内相对路径
		std::vector<std::string> dependencies;
	};
	*/

	// 解析 Meta 文件
	PluginMeta analysisMeta(std::string strMeta, std::string pathOrigin, std::filesystem::path pathParent) {
		PluginMeta plugin_meta;

		plugin_meta.origin = SPTool::PathToChar(pathOrigin);
		try {
			nlohmann::json jsonMeta(strMeta);

			if (jsonMeta.contains("name") && jsonMeta["name"].is_string()) {
				plugin_meta.name = jsonMeta["name"].get<std::string>();
			}
			else {
				throw std::runtime_error("meta.json missing name Field or Invalid type (Must be string)");
			}

			if (jsonMeta.contains("version") && jsonMeta["version"].is_string()) {
				plugin_meta.version = jsonMeta["version"].get<std::string>();
			}
			else {
				throw std::runtime_error("meta.json missing version field or Invalid type (Must be string)");
			}

			if (jsonMeta.contains("arch_version") && jsonMeta["arch_version"].is_number_integer()) {
				plugin_meta.arch_version = jsonMeta["arch_version"].get<int>();
			}
			else {
				throw std::runtime_error("meta.json missing arch_version field or Invalid type (Must be integer)");
			}

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
				throw std::runtime_error("meta.json missing type field or Invalid type (Must be string)");
			}

			if (jsonMeta.contains("entry") && jsonMeta["entry"].is_string()) {
				plugin_meta.entry_path = SPTool::PathToChar(pathParent / std::filesystem::path(jsonMeta["entry"].get<std::string>()));
			}
			else {
				throw std::runtime_error("meta.json missing entry field or Invalid type (Must be string)");
			}

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
					throw std::runtime_error("meta.json Dependencies must be array");
				}
			}

			std::string type_str = (plugin_meta.type == PluginType::object) ? "Object (Instance)" : "Function (Tool)";

			std::string deps_str = "None";
			if (!plugin_meta.dependencies.empty()) {
				deps_str = "";
				for (int i = 0; i < plugin_meta.dependencies.size(); ++i) {
					deps_str += plugin_meta.dependencies[i];
					if (i < plugin_meta.dependencies.size() - 1) deps_str += ", ";
				}
			}

			std::string debug_msg = std::format(
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
				plugin_meta.arch_version, plugin_meta.entry_path,
				plugin_meta.origin, deps_str
			);
			SPLog::debug(debug_msg);

		}
		catch (const nlohmann::json::parse_error& e) {
			SPLog::error("JSON Syntax Parse Failed: " + std::string(e.what()));
		}
		catch (const std::exception& e) {
			SPLog::error(std::string("Parse Exception: ") + e.what());
		}

		return plugin_meta;
	}
}
