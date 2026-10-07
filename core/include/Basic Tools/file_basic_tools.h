#pragma once
#include <nlohmann/json.hpp>

// 读取指定文件并转换为 Json
nlohmann::json readAllFileToJson(std::string path);
bool writeAllJsonToFile(std::string path, nlohmann::json);