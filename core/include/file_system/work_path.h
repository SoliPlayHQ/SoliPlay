#pragma once
#include <string>
#include <filesystem>

namespace SPFile {
    // 初始化工作目录
    void initWorkPath(void);

    // 获取执行目录，一般为程序根目录
    const std::filesystem::path& getExcutePath(void);

    // 获取写入目录，一般为可写入的安全目录
    const std::filesystem::path& getWritePath(void);
}