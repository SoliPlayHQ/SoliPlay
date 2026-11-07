#pragma once
#include <string>

namespace SPFile {
    // 初始化工作目录
    void initWorkPath(void);

    // 获取执行目录，一般为程序根目录
    std::string getExcutePath(void);

    // 获取写入目录，一般为可写入的安全目录
    std::string getWritePath(void);
}