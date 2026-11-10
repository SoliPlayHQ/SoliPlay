#include <file_system/work_path.h>
#include <tool_functions/path_tools.h>
#include <log_system.h>
#include <filesystem>

#include <windows.h>
#include <shlobj.h>

// [O] 已完成实机可行性测试

namespace SPFile {
    static std::filesystem::path pathExcute;
    static std::filesystem::path pathWrite;

    // 初始化工作目录
    void initWorkPath(void) {
        // 获取执行目录
#ifdef _WIN32
        wchar_t path[MAX_PATH];
        DWORD len = GetModuleFileNameW(NULL, path, MAX_PATH);
        pathExcute = std::filesystem::path(path).parent_path();
        SPLog::info("Get Excution Directory Path: " + SPTool::PathtoChar(pathExcute));

        // 获取写入目录
        PWSTR pszPath = nullptr;
        HRESULT hResult = SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, nullptr, &pszPath);
        if (SUCCEEDED(hResult)) {
            std::filesystem::path pathAppdata(pszPath);
            pathAppdata /= "SoliPlay";
            CoTaskMemFree(pszPath);

            std::error_code ec;
            std::filesystem::create_directories(pathAppdata, ec);
            if (ec) {
                SPLog::fatal("Can't Create Safety Directory!");
                throw std::runtime_error("Can't Create Safety Directory: " + ec.message());
            }

            pathWrite = pathAppdata;
        }
        else {
            SPLog::fatal("Can't Get Safety Directory!");
            pathWrite = pathExcute;
        }
        SPLog::info("Get Safety Directory Path: " + SPTool::PathtoChar(pathWrite));
#endif
    }

    // 获取执行目录，一般为程序根目录
    const std::filesystem::path& getExcutePath(void) {
        return pathExcute;
    }

    // 获取写入目录，一般为可写入的安全目录
    const std::filesystem::path& getWritePath(void) {
        return pathWrite;
    }
}